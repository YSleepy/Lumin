1.软件使用无边框窗口，自定义标题栏LuminWidgetBar。标题栏内可容纳菜单栏
2.软件在LuminWidgetBar下方预留工具栏LuminToolBar，可以先写一个占位
3.然后就是软件的主体，采用VS风格停靠布局：
    1.Dock必须要可复用，可以用于其他项目
    2.Dock必须支持qml
    3.D:\XDY\XDY\XDY_Project\github-online\QtFlex5 这是一个使用QWidget实现的Dock，可以参考