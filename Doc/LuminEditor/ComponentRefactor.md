# LuminEditor 组件重构说明

## 概述

本次重构将 LuminEditor 的 UI 组件系统改造为更通用、可复用的组件库。

## 新增基础组件 (Resources/Common/)

### 1. LuminButton
通用按钮组件，支持自定义颜色、圆角、hover 效果。

**属性：**
- `textColor` - 文本颜色
- `textHoverColor` - hover 时文本颜色
- `backgroundColor` - 背景颜色
- `hoverColor` - hover 时背景颜色
- `pressedColor` - 按下时背景颜色
- `buttonRadius` - 圆角半径

**使用示例：**
```qml
LuminButton {
    text: "确定"
    onClicked: console.log("Button clicked")
}
```

### 2. LuminToolButton
工具栏按钮组件，支持图标文本、tooltip。

**属性：**
- `iconText` - 图标文本（可以是 Unicode 符号）
- `iconSize` - 图标字体大小
- `buttonRadius` - 圆角半径
- 继承 LuminButton 的所有属性

**使用示例：**
```qml
LuminToolButton {
    iconText: "▶"
    iconSize: 14
    ToolTip.text: "Run"
    ToolTip.visible: hovered
    onClicked: console.log("Run")
}
```

### 3. LuminMenuBar
菜单栏容器，提供统一的菜单样式。

**属性：**
- `itemSpacing` - 菜单项间距
- `textColor` - 文本颜色
- `textHoverColor` - hover 时文本颜色
- `hoverColor` - hover 时背景颜色
- `itemRadius` - 圆角半径

**使用示例：**
```qml
LuminMenuBar {
    LuminMenu {
        title: "文件"
        LuminMenuItem { text: "打开"; onTriggered: openFile() }
        LuminMenuItem { text: "保存"; onTriggered: saveFile() }
    }
}
```

### 4. LuminMenu
单个菜单组件，可包含多个 MenuItem。

**属性：**
- `backgroundColor` - 下拉面板背景色
- `borderColor` - 边框颜色
- `menuRadius` - 圆角半径
- `menuBorderWidth` - 边框宽度

### 5. LuminMenuItem
菜单项组件。

**属性：**
- `textColor` - 文本颜色
- `textHighlightColor` - 高亮时文本颜色
- `highlightColor` - 高亮背景颜色
- `itemRadius` - 圆角半径

### 6. LuminSeparator
分隔符组件，支持水平和垂直方向。

**属性：**
- `horizontal` - 是否水平（默认 false，垂直）
- `separatorColor` - 颜色
- `thickness` - 粗细
- `length` - 长度

**使用示例：**
```qml
LuminSeparator {
    horizontal: false
    length: 20
}
```

### 7. LuminWindowButtons
窗口控制按钮组（最小化、最大化/还原、关闭）。

**属性：**
- `targetWindow` - 目标窗口对象
- `buttonWidth` - 按钮宽度
- `buttonHeight` - 按钮高度

## 重构的核心组件

### LuminWidgetBar (标题栏)

**改进：**
- 使用 RowLayout 替代手动位置计算
- 分离窗口控制按钮为独立组件 LuminWindowButtons
- 清理调试代码
- menuBar 通过 parent 重设置自动布局

**属性：**
- `title` - 标题文本
- `iconSource` - 图标路径
- `backgroundColor` - 背景颜色
- `targetWindow` - 目标窗口
- `menuBar` - 菜单栏组件（可选）

**布局结构：**
```
RowLayout:
  - LeftSection (Icon + Title)
  - MenuBarContainer (动态注入 menuBar)
  - DragArea (填充剩余空间，可拖拽)
  - WindowButtons (右对齐)
```

### LuminToolBar (工具栏)

**改进：**
- 完全数据驱动（通过 `toolItems` 属性）
- 支持按钮和分隔符两种类型
- 使用 Repeater + Loader 动态加载
- 移除所有硬编码按钮

**属性：**
- `toolItems` - 工具项数组，每项可以是：
  ```javascript
  {
    type: "button" | "separator",
    icon: "▶",           // 图标文本
    tooltip: "Run",       // tooltip 文本
    iconSize: 14,         // 图标大小
    width: 32,            // 按钮宽度
    height: 28,           // 按钮高度
    enabled: true,        // 是否启用
    action: function() {} // 点击回调
  }
  ```

**使用示例：**
```qml
LuminToolBar {
    toolItems: [
        { type: "button", icon: "▤", tooltip: "New", action: function() { console.log("New") } },
        { type: "separator" },
        { type: "button", icon: "▶", tooltip: "Run", action: function() { console.log("Run") } }
    ]
}
```

### LuminMainMenuBar (主菜单栏)

**改进：**
- 基于 LuminMenuBar 和 LuminMenu 构建
- 移除硬编码样式，统一使用 Common 组件
- 易于扩展和修改菜单项

## 使用方式

### 在 main.qml 中使用

```qml
import "Resources/Bar"
import "Resources/Common"

ApplicationWindow {
    id: mainWindow
    
    ColumnLayout {
        // 标题栏
        LuminWidgetBar {
            Layout.fillWidth: true
            title: "Lumin"
            targetWindow: mainWindow
            menuBar: mainMenuBar
        }
        
        // 菜单栏（单独声明，由 LuminWidgetBar 注入）
        LuminMainMenuBar {
            id: mainMenuBar
            visible: false  // 由 LuminWidgetBar 控制显示
        }
        
        // 工具栏
        LuminToolBar {
            Layout.fillWidth: true
            toolItems: [
                { type: "button", icon: "▤", tooltip: "New", action: newFile },
                { type: "separator" },
                { type: "button", icon: "▶", tooltip: "Run", action: runProject }
            ]
        }
        
        // 主内容区域
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
    
    function newFile() { console.log("New file") }
    function runProject() { console.log("Run project") }
}
```

## 组件特点

1. **高度可定制**：所有颜色、尺寸、样式都可通过属性覆盖
2. **主题感知**：默认使用 LuminTheme 单例，支持明暗主题切换
3. **数据驱动**：工具栏等组件支持完全数据驱动，易于动态修改
4. **组件分离**：窗口控制按钮、分隔符等拆分为独立组件，提高复用性
5. **布局简洁**：使用 Layout 自动布局，减少手动计算

## 目录结构

```
LuminEditor/
  Resources/
    Common/           # 通用基础组件
      qmldir
      LuminButton.qml
      LuminToolButton.qml
      LuminMenuBar.qml
      LuminMenu.qml
      LuminMenuItem.qml
      LuminSeparator.qml
      LuminWindowButtons.qml
    Bar/              # 标题栏、工具栏等
      LuminWidgetBar.qml
      LuminMainMenuBar.qml
      LuminToolBar.qml
    Theme/            # 主题
      LuminTheme.qml
    Dock/             # 停靠面板
      LuminDockContent.qml
```

## 下一步改进建议

1. **图标系统**：引入字体图标（如 Font Awesome）替代 Unicode 符号
2. **快捷键支持**：为菜单项添加快捷键显示和绑定
3. **状态持久化**：保存工具栏自定义配置
4. **更多基础组件**：输入框、复选框、下拉框等
5. **动画效果**：添加更流畅的过渡动画
