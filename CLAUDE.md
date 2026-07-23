# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Run

- **Open solution:** `Lumin.sln` in Visual Studio 2022
- **Toolchain:** MSVC v142 (VS2019), C++17, Qt 6.5.3_msvc2019_64
- **Platform:** x64 only (Debug / Release)
- No CLI build or automated tests — this is a learning project

## Architecture: Module Split

详见 `Doc/Lumin架构设计.md`

### 1.1 模块总览

```
                        Applications
  ┌─────────────────┐    ┌──────────────────┐
  │ LuminEditor.exe │    │ LuminRuntime.exe  │
  │  Qt Quick 应用   │    │  游戏独立启动器    │
  └────────┬────────┘    └────────┬─────────┘
           │                      │
  ┌────────┴──────────────────────┴─────────┐
  │              Platform 层                  │
  │  ┌─────────────────┐ ┌────────────────┐  │
  │  │ PlatformQt.dll   │ │ PlatformXXX.dll│  │
  │  │ (当前实现)       │ │ (未来可扩展)    │  │
  │  └─────────────────┘ └────────────────┘  │
  │     统一实现 IWindow / InputState         │
  └──────────────────────┬───────────────────┘
                         │
  ┌──────────────────────┴───────────────────┐
  │           LuminEngine.dll                │
  │           (纯 C++17，零 Qt)               │
  │  ┌──────┐ ┌──────┐ ┌──────┐ ┌────────┐  │
  │  │GamePlay│ │Render│ │Resource│ │Platform│  │
  │  │ 子系统 │ │ 子系统│ │ 子系统 │ │Interface│ │
  │  └──────┘ └──────┘ └──────┘ └────────┘  │
  └──────────────────────────────────────────┘
                         │
  ┌──────────────────────┴───────────────────┐
  │               Game.dll                    │
  │            用户游戏逻辑                    │
  └──────────────────────────────────────────┘
```

### 1.2 模块职责

| 模块 | 类型 | Qt | 职责 |
|------|------|-----|------|
| **LuminEngine.dll** | 动态库 | **无** | 引擎核心 + 自研数学库 + 平台抽象接口 |
| **LuminPlatformQt.dll** | 动态库 | 有 | 平台层 Qt 实现（当前）：窗口/GL上下文/输入转换 |
| **LuminPlatformXXX.dll** | 动态库 | 视平台 | 平台层扩展（未来） |
| **LuminEditor.exe** | 可执行 | 有 | Qt Quick 编辑器：PIE/资源管理/打包 |
| **LuminRuntime.exe** | 可执行 | 有 | 独立游戏启动器：命令行/加载Game.dll/运行 |
| **Game.dll** | 动态库 | 仅通过引擎 | 用户游戏逻辑 |

### 1.3 依赖关系

```
Game.dll → LuminEngine.dll ← Platform 层 (Qt / XXX)
                ↑                    ↑
         Editor.exe + Runtime.exe ──┘
```

Engine Core 通过 `IWindow*` 消费窗口，不创建窗口。Platform 层是实现，Editor/Runtime 是消费者。三方通过 Platform 接口解耦。

---

## Engine Core (`LuminEngine`) 关键设计

### 平台抽象接口 (2.3)

`LEngine` 接收 `IWindow*`，不关心窗口是 Qt 还是 GLFW 创建的：

```cpp
struct EngineInitParams { IWindow* window; const char* gameRootPath; int targetFPS = 0; };

class IWindow {
    virtual bool ShouldClose() const = 0;
    virtual void SwapBuffers() = 0;
    virtual void PollEvents() = 0;
    virtual const InputState& GetInputState() const = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
    virtual float GetAspectRatio() const = 0;
};
```

`InputState` 是纯数据结构（键位数组 + 鼠标位置/按键），Platform 层负责从 Qt 事件填充。

### LuminEngine 第三方依赖替换 (2.5)

| Qt 类型 | 替换为 | 说明 |
|---------|--------|------|
| `QVector2D/3D` | `LVec2/3` | 自研数学库 |
| `QQuaternion` | `LQuat` | 自研 |
| `QMatrix4x4` | `LMat4` | 自研，列主序 |
| `QOpenGLFunctions_3_3_Core` | GLAD | 纯C函数指针 |
| `QOpenGLWidget` | 移出Core → IWindow | Core不知窗口类型 |
| `QByteArray` | `std::vector<uint8_t>` | STL |
| `QFile/QDir` | `std::filesystem` | C++17 |
| `QJson*` | nlohmann/json | header-only |
| `QImage` | stb_image | 已有 |
| `QDebug/QThread/QMutex` | 自研 LLog / std 等价物 | 纯 C++ |

### 属性系统与序列化 (2.6)

不实现完整反射。使用 **PropertyMap + 轻量基类**：

```cpp
using PropertyValue = std::variant<bool, int, float, std::string, LVec2, LVec3, LVec4, LQuat>;
using PropertyMap = std::unordered_map<std::string, PropertyValue>;

class GObject {
    virtual const char* GetTypeName() const = 0;   // 工厂创建
    virtual void GetProperties(PropertyMap& out) const;
    virtual void SetProperties(const PropertyMap& in);
protected:
    PropertyMap m_properties;  // 属性编辑器和序列化共用
};
```

序列化 = 遍历 PropertyMap → JSON。反序列化 = JSON → TypeRegistry 工厂创建 → 回填 PropertyMap。与属性编辑器共享同一份数据，不需要反射宏。

---

## Engine Editor (`LuminEditor`)

**入口:** `main.cpp` — `QApplication` + `qmlRegisterType<LMarkdownView>` + `QQmlApplicationEngine` 加载 main.qml

**QML 文件 (`Resources/`):**
| 文件 | 用途 |
|------|------|
| `main.qml` | 主窗口：4方向停靠区 + 停靠提示 + `openMathDoc()` |
| `TitleBar.qml` | 标题栏：菜单栏 + 窗口按钮 + 拖拽移动 |
| `EditorMenuBar.qml` | 菜单：文件/编辑/Git/项目/帮助 |
| `WindowButtons.qml` | 最小化/最大化/关闭按钮 |
| `DockHintOverlay.qml` | 停靠提示（拖拽窗口时蓝色高亮） |
| `MathDocPanel.qml` | 数学文档面板（工具栏 + LMarkdownView） |
| `MathDocWindow.qml` | 浮动窗口（标题栏 + MathDocPanel + 拖拽→停靠） |

**关键 C++ 类:** `LMarkdownView` — QQuickPaintedItem 包装 QMarkdownTextEdit（ThirdParty/qmarkdowntextedit 子模块）

## Coding Conventions

1. **文件名** = 主类名，如 `LEngine.h` / `LEngine.cpp`
2. **类名、函数名** — 大驼峰 (PascalCase)，如 `GetWorldPosition()`
3. **引擎类前缀** `L` — `LEngine`, `LShader`, `LMesh`, `LInputManager`
4. **GamePlay 类前缀** `G` — `GActor`, `GWorld`, `GComponent`, `GPlayerController`
5. **常量/宏** — 全大写下划线，如 `MAX_KEYS`, `ENGINE_API`
6. **成员变量** — 前缀 `m_`，如 `m_objectId`, `m_components`
7. **静态函数** — 前缀 `Static_`，如 `Static_Zero()`, `Static_One()`
8. **Q_INVOKABLE / QML 暴露函数** — 小驼峰，如 `loadFile()`, `setMarkdownText()`

**Namespaces:** `Lumin` (引擎), `Lumin::Math` (数学), `EngineRuntime` (运行时)

## Key Conventions

- Header-only 优先，非平凡实现才用 .cpp
- 线程分离：游戏逻辑线程 + 渲染线程，通过 `LRenderQueue` 互斥同步
- 不主动 git commit，用户自己管理提交
