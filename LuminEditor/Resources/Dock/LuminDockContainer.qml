import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Control {
    id: dockRoot

    property Item layoutRoot: null
    property Item draggingItem: null

    // ── Public API ──

    function createItem(title) {
        var item = dockItemComponent.createObject(null, { dockTitle: title })
        return item
    }

    function addDockItem(item, area, targetPane) {
        if (!targetPane)
            targetPane = findTargetPane()

        if (!targetPane) {
            // No layout yet — create initial pane
            var pane = paneComponent.createObject(layoutArea)
            pane.anchors.fill = layoutArea
            layoutRoot = pane
            dockCenter(item, pane)
            return
        }

        switch (area) {
            case "center": dockCenter(item, targetPane); break
            case "left":   dockEdge(item, targetPane, Qt.Horizontal, 0); break
            case "right":  dockEdge(item, targetPane, Qt.Horizontal, 1); break
            case "top":    dockEdge(item, targetPane, Qt.Vertical, 0); break
            case "bottom": dockEdge(item, targetPane, Qt.Vertical, 1); break
        }
    }

    function dockCenter(item, targetPane) {
        detachFromLayout(item)
        targetPane.addItem(item)
    }

    function dockEdge(item, targetPane, orientation, position) {
        detachFromLayout(item)

        var pSplit = targetPane.parentSplit

        if (!pSplit) {
            // targetPane is root — create root split
            var rootSplit = splitComponent.createObject(layoutArea)
            rootSplit.orientation = orientation
            rootSplit.anchors.fill = layoutArea
            targetPane.anchors.fill = undefined
            layoutRoot = rootSplit

            var np0 = paneComponent.createObject(null)
            np0.addItem(item)

            if (position === 0) {
                rootSplit.addChildDirect(np0)
                rootSplit.addChildDirect(targetPane)
            } else {
                rootSplit.addChildDirect(targetPane)
                rootSplit.addChildDirect(np0)
            }
            targetPane.parentSplit = rootSplit
            np0.parentSplit = rootSplit

        } else if (pSplit.orientation === orientation) {
            // Same orientation — add to existing split
            var np1 = paneComponent.createObject(null)
            np1.addItem(item)

            if (position === 0) {
                pSplit.removeChildDirect(targetPane)
                pSplit.addChildDirect(np1)
                pSplit.addChildDirect(targetPane)
            } else {
                pSplit.addChildDirect(np1)
            }
            targetPane.parentSplit = pSplit
            np1.parentSplit = pSplit

        } else {
            // Different orientation — wrap targetPane in nested split
            var nested = splitComponent.createObject(null)
            nested.orientation = orientation

            pSplit.removeChildDirect(targetPane)

            var np2 = paneComponent.createObject(null)
            np2.addItem(item)

            if (position === 0) {
                nested.addChildDirect(np2)
                nested.addChildDirect(targetPane)
            } else {
                nested.addChildDirect(targetPane)
                nested.addChildDirect(np2)
            }
            targetPane.parentSplit = nested
            np2.parentSplit = nested

            pSplit.addChildDirect(nested)
            nested.parentSplit = pSplit
        }
    }

    function detachFromLayout(item) {
        if (!item || !item.pane)
            return
        var pane = item.pane
        pane.removeItemDirect(item)
        if (pane.tabCount === 0)
            removeEmptyPane(pane)
    }

    function removeEmptyPane(pane) {
        var pSplit = pane.parentSplit
        if (!pSplit) {
            // pane is root
            if (layoutRoot === pane) {
                pane.destroy()
                layoutRoot = null
            }
            return
        }

        pSplit.removeChildDirect(pane)
        pane.destroy()

        var remainCount = pSplit.childCount()
        if (remainCount === 0) {
            var gSplit = pSplit.parentSplit
            if (gSplit) {
                gSplit.removeChildDirect(pSplit)
            }
            pSplit.destroy()
            if (layoutRoot === pSplit)
                layoutRoot = null
        } else if (remainCount === 1) {
            // Collapse: promote the remaining child
            var r = pSplit.childAt(0)
            var gSplit2 = pSplit.parentSplit
            pSplit.removeChildDirect(r)
            if (gSplit2) {
                gSplit2.removeChildDirect(pSplit)
                gSplit2.addChildDirect(r)
                r.parentSplit = gSplit2
            } else {
                r.parent = layoutArea
                r.anchors.fill = layoutArea
                r.parentSplit = null
                layoutRoot = r
            }
            pSplit.destroy()
        }
    }

    // ── Drag (click-based: click title → click zone) ──

    function startDrag(item) {
        draggingItem = item
    }

    function cancelDrag() {
        draggingItem = null
    }

    function executeDrop(zone) {
        if (!draggingItem)
            return
        var item = draggingItem
        draggingItem = null

        var target = findPaneAt(
            item.mapToItem(dockRoot, item.width / 2, item.height / 2).x,
            item.mapToItem(dockRoot, item.width / 2, item.height / 2).y
        )
        if (!target)
            target = findTargetPane()
        if (!target) {
            target = paneComponent.createObject(layoutArea)
            target.anchors.fill = layoutArea
            layoutRoot = target
        }

        switch (zone) {
            case LuminDockDropOverlay.Zone.Center:
                dockCenter(item, target); break
            case LuminDockDropOverlay.Zone.Left:
                dockEdge(item, target, Qt.Horizontal, 0); break
            case LuminDockDropOverlay.Zone.Right:
                dockEdge(item, target, Qt.Horizontal, 1); break
            case LuminDockDropOverlay.Zone.Top:
                dockEdge(item, target, Qt.Vertical, 0); break
            case LuminDockDropOverlay.Zone.Bottom:
                dockEdge(item, target, Qt.Vertical, 1); break
        }
    }

    // ── Tree queries ──

    function findTargetPane() {
        if (!layoutRoot) return null
        if (layoutRoot.dockType === "pane") return layoutRoot
        return findFirstPane(layoutRoot)
    }

    function findFirstPane(node) {
        if (!node) return null
        if (node.dockType === "pane") return node
        for (var i = 0; i < node.childCount(); i++) {
            var f = findFirstPane(node.childAt(i))
            if (f) return f
        }
        return null
    }

    function findPaneAt(x, y) {
        return findPaneAtNode(layoutRoot, x, y)
    }

    function findPaneAtNode(node, x, y) {
        if (!node) return null
        if (node.dockType === "pane") {
            var pos = mapToItem(node, x, y)
            if (pos.x >= 0 && pos.x <= node.width && pos.y >= 0 && pos.y <= node.height)
                return node
            return null
        }
        for (var i = 0; i < node.childCount(); i++) {
            var f = findPaneAtNode(node.childAt(i), x, y)
            if (f) return f
        }
        return null
    }

    // ── Visual ──

    implicitWidth: 400
    implicitHeight: 300

    background: Rectangle {
        color: "#1e1e1e"
    }

    contentItem: Item {
        id: layoutArea
        anchors.fill: parent
        clip: true
    }

    LuminDockDropOverlay {
        id: dropOverlay
        active: dockRoot.draggingItem !== null
        onDropped: function(zone) { dockRoot.executeDrop(zone) }
    }

    Rectangle {
        id: dragGhost
        z: 1001
        visible: false
        width: 160; height: 30
        color: "#007acc"
        opacity: 0.8
        radius: 4
        Text {
            anchors.centerIn: parent
            text: dockRoot.draggingItem ? dockRoot.draggingItem.dockTitle : ""
            color: "white"
            font.pixelSize: 12
        }
    }

    // ── Components ──

    Component {
        id: dockItemComponent
        LuminDockItem {
            onDragStarted: {
                if (dockRoot.draggingItem === null)
                    dockRoot.startDrag(this)
            }
        }
    }

    Component {
        id: paneComponent
        LuminDockPane {}
    }

    Component {
        id: splitComponent
        LuminDockSplit {}
    }
}
