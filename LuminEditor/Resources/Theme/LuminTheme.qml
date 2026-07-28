pragma Singleton
import QtQuick

QtObject {
    // ── Theme name (switch by changing this property) ──
    property string activeTheme: "dark"

    // ── Convenience aliases (bound to active theme) ──
    readonly property color bg0: activeTheme === "dark" ? "#2d2d30" : "#f0f0f0"
    readonly property color bg1: activeTheme === "dark" ? "#252526" : "#ffffff"
    readonly property color bg2: activeTheme === "dark" ? "#1e1e1e" : "#fafafa"
    readonly property color bg3: activeTheme === "dark" ? "#333337" : "#e0e0e0"

    readonly property color textMain: activeTheme === "dark" ? "#ffffff" : "#1e1e1e"
    readonly property color textSoft: activeTheme === "dark" ? "#cccccc" : "#555555"
    readonly property color textDim:  activeTheme === "dark" ? "#7f8899" : "#999999"

    readonly property color frame:       activeTheme === "dark" ? "#3f3f46" : "#d0d0d0"
    readonly property color separator:   activeTheme === "dark" ? "#404040" : "#e0e0e0"

    readonly property color hoverBg:      activeTheme === "dark" ? "#3e3e3e" : "#d0d0d0"
    readonly property color hoverBlue:    "#094771"
    readonly property color hoverWinBtn:  activeTheme === "dark" ? "#34495e" : "#d0d0d0"
    readonly property color closeRed:     activeTheme === "dark" ? "#e74c3c" : "#c0392b"

    readonly property color accent:       "#007acc"
    readonly property color accentLight:  "#1c97ea"
    readonly property color accentDark:   "#0e6198"

    readonly property int titleBarHeight: 30
    readonly property int toolBarHeight:  36
    readonly property int radius:         4
    readonly property int menuSpacing:    8
}
