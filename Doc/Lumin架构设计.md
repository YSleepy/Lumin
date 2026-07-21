# Lumin 引擎架构设计文档

## 1. 模块划分

### 1.1 模块总览

```
┌──────────────────────────────────────────────────────────────────┐
│                        Applications                               │
│                                                                   │
│  ┌─────────────────────┐    ┌──────────────────────────────┐     │
│  │   LuminEditor.exe   │    │     LuminRuntime.exe          │     │
│  │   Qt Quick 应用      │    │     游戏独立启动器            │     │
│  │                     │    │                              │     │
│  │  - QML 编辑器 UI    │    │  - 命令行 (new/run/build)    │     │
│  │  - Play In Editor   │    │  - 加载 Game.dll            │     │
│  │  - 资源管理         │    │  - 全屏游戏循环             │     │
│  │  - 打包发布         │    │                              │     │
│  └──────────┬──────────┘    └───────────────┬──────────────┘     │
│             │                               │                     │
│  ┌──────────┴───────────────────────────────┴──────────────┐     │
│  │                    Platform 层                            │     │
│  │                                                          │     │
│  │  ┌──────────────────────┐  ┌────────────────────────┐   │     │
│  │  │ LuminPlatformQt.dll  │  │ LuminPlatformXXX.dll   │   │     │
│  │  │ (当前实现)           │  │ (未来可扩展)            │   │     │
│  │  └──────────────────────┘  └────────────────────────┘   │     │
│  │                                                          │     │
│  │  统一实现 IWindow / InputState / OpenGL Context          │     │
│  └──────────────────────────┬───────────────────────────────┘     │
│                             │                                     │
│  ┌──────────────────────────┴───────────────────────────────┐     │
│  │                   LuminEngine.dll                         │     │
│  │                   (纯 C++17，零 Qt)                        │     │
│  │                                                           │     │
│  │  ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌────────────┐  │     │
│  │  │ GamePlay │ │  Render  │ │ Resource │ │  Platform   │  │     │
│  │  │ 子系统   │ │  子系统   │ │  子系统   │ │  Interface  │  │     │
│  │  └──────────┘ └──────────┘ └──────────┘ └────────────┘  │     │
│  └──────────────────────────────────────────────────────────┘     │
│                                                                   │
│  ┌──────────────────────────────────────────────────────────┐     │
│  │                     Game.dll                               │     │
│  │                     用户游戏逻辑                            │     │
│  └──────────────────────────────────────────────────────────┘     │
└──────────────────────────────────────────────────────────────────┘
```

### 1.2 各模块职责

| 模块 | 类型 | Qt依赖 | 职责 |
|------|------|--------|------|
| **LuminEngine.dll** | 动态库 | **无** | 引擎核心：GamePlay框架、渲染系统、资源管理、**自研数学库**、日志、平台抽象接口 |
| **LuminPlatformQt.dll** | 动态库 | **有** | 平台层 Qt 实现（当前）：窗口、OpenGL上下文、输入转换 |
| **LuminPlatformXXX.dll** | 动态库 | 视平台而定 | 平台层扩展（未来）：非 Qt 平台的窗口+GL上下文实现 |
| **LuminEditor.exe** | 可执行 | **有** | **Qt Quick (QML)** 编辑器：场景编辑、PIE、资源管理、项目打包 |
| **LuminRuntime.exe** | 可执行 | **有** | 独立游戏启动器：加载项目、运行游戏循环 |
| **Game.dll** | 动态库 | 仅通过引擎 | 用户游戏逻辑：实现 GameInstance/Actor/Component |

### 1.3 模块间依赖关系

```
                    ┌──────────────────────┐
                    │     Game.dll          │
                    │   (用户游戏逻辑)       │
                    └──────────┬───────────┘
                               │ 依赖
                    ┌──────────▼───────────┐
                    │   LuminEngine.dll     │
                    │   (引擎核心，纯C++)    │
                    │                      │
                    │ 内部结构:             │
                    │ ├─ Platform/         │
                    │ │  IWindow           │
                    │ │  InputState        │
                    │ ├─ GamePlay/         │
                    │ ├─ Render/           │
                    │ ├─ Resource/         │
                    │ ├─ Math/ (自研)       │
                    │ └─ Core/ (Log等)     │
                    └──────────┬───────────┘
                               │ 不依赖具体平台
                               │
         ┌─────────────────────┼─────────────────────────────┐
         │                     │                             │
         │         ┌───────────┴───────────┐                 │
         │         │     Platform 层       │                 │
         │         │  ┌─────────────────┐  │                 │
         │         │  │ PlatformQt      │  │                 │
         │         │  │ (当前实现)      │  │                 │
         │         │  │                │  │                 │
         │         │  │ IWindow        │  │                 │
         │         │  │ GL Context     │  │                 │
         │         │  │ Qt事件→Input   │  │                 │
         │         │  └─────────────────┘  │                 │
         │         │  ┌─────────────────┐  │                 │
         │         │  │ PlatformXXX     │  │                 │
         │         │  │ (未来扩展)      │  │                 │
         │         │  └─────────────────┘  │                 │
         │         └───────────┬───────────┘                 │
         │                     │                             │
         │         ┌───────────┴───────────┐                 │
         │         │                     │                 │
         │   ┌─────┴─────┐         ┌─────┴─────┐           │
         │   │  Editor   │         │  Runtime   │           │
         │   │(Qt Quick) │         │ (启动器)   │           │
         │   └───────────┘         └───────────┘           │
         │                                                 │
         │   应用层通过平台接口使用窗口，不依赖具体实现        │
```

---

## 2. 引擎核心详细设计 (LuminEngine.dll)

### 2.1 目录结构

```
LuminEngine/
├── Src/
│   ├── Core/                    # 引擎核心
│   │   ├── Engine.h/cpp         # LEngine 单例（不再创建窗口）
│   │   ├── EngineConfig.h       # 引擎配置
│   │   ├── GameLoop.h/cpp       # 主循环逻辑
│   │   ├── PropertyValue.h      # 属性值类型 (std::variant)
│   │   ├── TypeRegistry.h/cpp   # 类型注册表（工厂）
│   │   └── WorldSerializer.h/cpp# World 序列化/反序列化
│   │
│   ├── Math/                    # 自研数学库（纯 C++，无外部依赖）
│   │   ├── LMath.h              # 统一包含
│   │   ├── LVec2.h              # 二维向量
│   │   ├── LVec3.h/cpp          # 三维向量
│   │   ├── LVec4.h              # 四维向量
│   │   ├── LMat3.h              # 3×3 矩阵
│   │   ├── LMat4.h/cpp          # 4×4 矩阵
│   │   ├── LQuat.h/cpp          # 四元数
│   │   ├── LTransform.h         # 位置/旋转/缩放结构体
│   │   └── LMathCommon.h        # 常量 (PI, DEG2RAD 等) + 工具函数
│   │
│   ├── Platform/                # 平台抽象接口（纯虚类 + 数据结构）
│   │   ├── IWindow.h            # 窗口接口
│   │   ├── InputState.h         # 输入状态（纯数据）
│   │   └── PlatformTypes.h      # 平台无关类型定义
│   │
│   ├── GamePlay/                # GamePlay 框架
│   │   ├── GObject.h/cpp
│   │   ├── GWorld.h/cpp
│   │   ├── GLevel.h/cpp
│   │   ├── GActor.h/cpp
│   │   ├── Component/
│   │   │   ├── GComponent.h/cpp
│   │   │   ├── GSceneComponent.h/cpp
│   │   │   ├── GNonSceneComponent.h/cpp
│   │   │   ├── GMeshSceneComponent.h/cpp
│   │   │   ├── GCameraComponent.h/cpp
│   │   │   └── GLightComponent.h/cpp
│   │   └── GameMode/
│   │       ├── GGameModeBase.h
│   │       ├── GController.h/cpp
│   │       └── GPlayerController.h/cpp
│   │
│   ├── Render/                  # 渲染系统
│   │   ├── LGraphicsCore.h/cpp  # 封装 GLAD 的 OpenGL 调用
│   │   ├── LShader.h/cpp
│   │   ├── LTexture.h/cpp
│   │   ├── LVertexLayout.h
│   │   ├── LRenderQueue.h/cpp   # 线程安全渲染队列
│   │   ├── LMaterial.h/cpp
│   │   └── LMesh.h/cpp
│   │
│   ├── Resource/                # 资源管理
│   │   ├── LFileSystem.h/cpp    # 路径管理 (std::filesystem)
│   │   ├── LResourceManager.h/cpp
│   │   ├── LGltfUtils.h/cpp     # glTF 加载
│   │   └── LAssetCooker.h/cpp   # 资源烘焙（编辑器使用）
│   │
│   ├── Game/                    # 游戏端暴露的接口
│   │   ├── LGameModuleBase.h/cpp
│   │   └── LGameInstanceBase.h/cpp
│   │
│   └── Log/                     # 日志系统
│       └── LLog.h/cpp           # 纯 C++ 日志
│
└── ThirdParty/
    ├── glad/                    # GLAD (OpenGL loader)
    ├── tiny_gltf/               # glTF loader
    ├── stb_image/               # 图片加载
    └── nlohmann/                # JSON (header-only)
```

### 2.2 自研数学库设计

不引入 GLM，自己实现引擎所需的数学类型。API 风格参考 GLSL/HLSL，内存布局与 OpenGL 兼容。

```cpp
// LuminEngine/Src/Math/LVec3.h
namespace Lumin {

struct LVec3 {
    float x, y, z;

    // 构造函数
    LVec3() : x(0), y(0), z(0) {}
    LVec3(float v) : x(v), y(v), z(v) {}
    LVec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // 常用静态
    static LVec3 Zero()    { return {0, 0, 0}; }
    static LVec3 One()     { return {1, 1, 1}; }
    static LVec3 Up()      { return {0, 1, 0}; }
    static LVec3 Forward() { return {0, 0, -1}; }
    static LVec3 Right()   { return {1, 0, 0}; }

    // 运算符
    LVec3 operator+(const LVec3& v) const { return {x+v.x, y+v.y, z+v.z}; }
    LVec3 operator-(const LVec3& v) const { return {x-v.x, y-v.y, z-v.z}; }
    LVec3 operator*(float s) const { return {x*s, y*s, z*s}; }
    LVec3 operator/(float s) const { return {x/s, y/s, z/s}; }
    LVec3 operator-() const { return {-x, -y, -z}; }

    LVec3& operator+=(const LVec3& v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
    LVec3& operator-=(const LVec3& v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
    LVec3& operator*=(float s) { x*=s; y*=s; z*=s; return *this; }

    // 向量运算
    float Length() const;
    float LengthSquared() const { return x*x + y*y + z*z; }
    LVec3 Normalized() const;
    float Dot(const LVec3& v) const { return x*v.x + y*v.y + z*v.z; }
    LVec3 Cross(const LVec3& v) const;
};

// 标量 * 向量
inline LVec3 operator*(float s, const LVec3& v) { return v * s; }

} // namespace Lumin
```

```cpp
// LuminEngine/Src/Math/LVec4.h
namespace Lumin {

struct LVec4 {
    float x, y, z, w;

    LVec4() : x(0), y(0), z(0), w(0) {}
    LVec4(float v) : x(v), y(v), z(v), w(v) {}
    LVec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    LVec4(const LVec3& xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

    LVec3 xyz() const { return {x, y, z}; }

    // 运算符同 LVec3...
};

} // namespace Lumin
```

```cpp
// LuminEngine/Src/Math/LMat4.h
namespace Lumin {

struct LMat4 {
    // 列主序，与 OpenGL/GLSL 一致
    // mat[col][row]
    float m[4][4];

    LMat4(); // 单位矩阵

    static LMat4 Identity();
    static LMat4 Translate(const LVec3& pos);
    static LMat4 Rotate(const LQuat& rot);
    static LMat4 Scale(const LVec3& scale);
    static LMat4 LookAt(const LVec3& eye, const LVec3& center, const LVec3& up);
    static LMat4 Perspective(float fov, float aspect, float near, float far);
    static LMat4 Ortho(float left, float right, float bottom, float top,
                       float near, float far);

    LMat4 operator*(const LMat4& other) const;
    LVec4 operator*(const LVec4& v) const;

    LMat4 Inverse() const;
    LMat4 Transpose() const;

    const float* Data() const { return &m[0][0]; }
};

} // namespace Lumin
```

```cpp
// LuminEngine/Src/Math/LQuat.h
namespace Lumin {

struct LQuat {
    float x, y, z, w; // w 为实部

    LQuat() : x(0), y(0), z(0), w(1) {}
    LQuat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    static LQuat Identity();
    static LQuat FromEuler(float pitch, float yaw, float roll);
    static LQuat FromAxisAngle(const LVec3& axis, float angle);

    LVec3 ToEuler() const;
    LQuat Normalized() const;
    LQuat Inverse() const { return {-x, -y, -z, w}; }

    LQuat operator*(const LQuat& q) const;  // 旋转组合
    LVec3 operator*(const LVec3& v) const;  // 旋转向量
};

} // namespace Lumin
```

```cpp
// LuminEngine/Src/Math/LTransform.h
namespace Lumin {

struct LTransform {
    LVec3 position   = LVec3::Zero();
    LQuat rotation   = LQuat::Identity();
    LVec3 scale      = LVec3::One();

    LMat4 ToMatrix() const;
    LMat4 ToInverseMatrix() const;
};

// 渲染使用的数据结构
struct CameraInfo {
    LMat4 ViewMatrix;
    LMat4 ProjectionMatrix;
};

struct LightInfo {
    LVec3 Position;
    LVec3 Color;
};

} // namespace Lumin
```

### 2.3 平台抽象接口

```cpp
// LuminEngine/Src/Platform/IWindow.h

namespace Lumin {

struct WindowDesc {
    const char* title;
    int width;
    int height;
    bool fullscreen;
};

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual bool ShouldClose() const = 0;
    virtual void SwapBuffers() = 0;
    virtual void PollEvents() = 0;
    virtual const InputState& GetInputState() const = 0;

    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
    virtual float GetAspectRatio() const = 0;
};

} // namespace Lumin
```

```cpp
// LuminEngine/Src/Platform/InputState.h

namespace Lumin {

struct InputState {
    static constexpr int MaxKeys = 256;
    static constexpr int MaxMouseButtons = 8;

    bool keys[MaxKeys]{false};
    bool mouseButtons[MaxMouseButtons]{false};
    float mouseX = 0.0f;
    float mouseY = 0.0f;
    float mouseDeltaX = 0.0f;
    float mouseDeltaY = 0.0f;

    bool IsKeyPressed(int key) const { return keys[key]; }
    bool IsMousePressed(int btn) const { return mouseButtons[btn]; }
};

enum class KeyCode : uint16_t {
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    Escape, Enter, Space, Tab, Backspace, Delete,
    LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt,
    Up, Down, Left, Right,
    MouseLeft, MouseRight, MouseMiddle,
};

} // namespace Lumin
```

### 2.4 LEngine 重新设计

```cpp
// LuminEngine/Src/Core/Engine.h

namespace Lumin {

struct EngineInitParams {
    IWindow* window;
    const char* gameRootPath;
    int targetFPS = 0;
};

class LEngine {
public:
    static LEngine& Get();

    bool Init(const EngineInitParams& params);
    void Run();               // 阻塞式主循环
    void Tick(float dt);      // 单帧 Tick（供编辑器模式控制）
    void Destroy();

    void SetGameInstance(LGameInstanceBase* instance);

    LGraphicsCore&     GetGraphics();
    LRenderQueue&      GetRenderQueue();
    LFileSystem&       GetFileSystem();
    LResourceManager&  GetResourceManager();
    const InputState&  GetInputState() const;

private:
    IWindow* m_window = nullptr;
};

} // namespace Lumin
```

```cpp
void LEngine::Run() {
    while (!m_window->ShouldClose() && !IsGameFinished()) {
        m_window->PollEvents();
        float dt = CalculateDeltaTime();
        Tick(dt);
        m_window->SwapBuffers();
    }
}

void LEngine::Tick(float dt) {
    m_gameInstance->Tick(dt);
    m_inputState = &m_window->GetInputState();
}
```

### 2.5 第三方依赖替换

| 当前依赖 (Qt) | 替换为 | 说明 |
|---------------|--------|------|
| `QVector2D/3D` | `LVec2/3` | 自研，纯C++，与GLSL内存布局兼容 |
| `QQuaternion` | `LQuat` | 自研，四元数 |
| `QMatrix4x4` | `LMat4` | 自研，列主序，与OpenGL一致 |
| `QOpenGLFunctions_3_3_Core` | GLAD | 纯 C 函数指针，无框架依赖 |
| `QOpenGLWidget` | 移出 Core → IWindow 接口 | Core 不知道窗口类型 |
| `QApplication` | 移出 Core → 应用层 | Core 无 Qt 事件循环 |
| `QByteArray` | `std::vector<uint8_t>` | C++ 标准库 |
| `QFile/QDir` | `std::filesystem` | C++17 标准库 |
| `QJson*` | nlohmann/json | header-only |
| `QImage` | stb_image | 已有依赖 |
| `QDebug` | 自研 LLog | 纯 C++，支持文件落盘 + 控制台 |
| `QThread` | `std::thread::id` | 仅用于日志标记 |
| `QMutex` | `std::mutex` | C++ 标准库 |
| `QDateTime` | `std::chrono` | C++ 标准库 |

---

### 2.6 属性系统与序列化

不实现 UE 式的完整反射（需要代码生成器，一个人维护不了）。使用 **属性包（PropertyMap）+ 轻量基类** 替代，同时满足属性编辑器和序列化的需求。

#### 设计原则

- **属性包**：`std::unordered_map<std::string, PropertyValue>` 存储属性值，属性编辑器和序列化都读它
- **轻量基类**：`GObject` 只加 3 个虚函数（`GetTypeName`、`GetProperties`、`SetProperties`），不做 UObject 式的重量级反射
- **无宏、无代码生成**：子类只需 override `GetTypeName()` 返回类名字符串

#### PropertyValue

```cpp
// LuminEngine/Src/Core/PropertyValue.h
// 使用 std::variant 支持常用属性类型

namespace Lumin {

using PropertyValue = std::variant<
    bool,
    int,
    float,
    std::string,
    Math::LVec2,
    Math::LVec3,
    Math::LVec4,
    Math::LQuat
>;

using PropertyMap = std::unordered_map<std::string, PropertyValue>;

} // namespace Lumin
```

#### GObject 扩展

```cpp
// GObject.h — 只加 3 个虚函数

namespace Lumin {

class GObject {
public:
    GObject();
    virtual ~GObject();

    // === 已有 ===
    uint32_t GetObjectId() const { return m_objectId; }
    const std::string& GetObjectName() const { return m_objectName; }

    // === 序列化接口（轻量，只有 3 个） ===
    
    // 每个子类返回唯一类型名，用于工厂创建
    virtual const char* GetTypeName() const = 0;

    // 导出/导入属性
    virtual void GetProperties(PropertyMap& out) const;
    virtual void SetProperties(const PropertyMap& in);

protected:
    uint32_t m_objectId;
    std::string m_objectName;

    // 属性存储 — 属性编辑器和序列化共用这个 map
    PropertyMap m_properties;
};

} // namespace Lumin
```

#### 类型注册表（工厂）

```cpp
// LuminEngine/Src/Core/TypeRegistry.h

namespace Lumin {

class TypeRegistry {
public:
    using FactoryFunc = std::function<std::unique_ptr<GObject>()>;

    static TypeRegistry& Get();

    // 注册类型
    template<typename T>
    void Register(const char* name) {
        m_factories[name] = []() -> std::unique_ptr<GObject> {
            return std::make_unique<T>();
        };
    }

    // 通过类型名创建实例
    std::unique_ptr<GObject> Create(const char* typeName) const;

private:
    std::unordered_map<std::string, FactoryFunc> m_factories;
};

// 注册宏 — 在 .cpp 中使用
#define L_REGISTER_TYPE(T) \
    static bool _reg_##T = []() { \
        TypeRegistry::Get().Register<T>(#T); \
        return true; \
    }()

} // namespace Lumin
```

#### 子类使用示例

```cpp
// GLightComponent.h
class GLightComponent : public GComponent {
public:
    const char* GetTypeName() const override { return "GLightComponent"; }

    GLightComponent(const std::string& name);

    // 对外仍是有类型的 getter/setter
    LVec3 GetColor() const;
    void SetColor(const LVec3& c);
};

// GLightComponent.cpp
GLightComponent::GLightComponent(const std::string& name) {
    // 向 PropertyMap 注册属性
    m_properties["Color"]     = Math::LVec3(1.0f, 1.0f, 1.0f);
    m_properties["Intensity"] = 1.0f;
    m_properties["Range"]     = 10.0f;
}

LVec3 GLightComponent::GetColor() const {
    return std::get<Math::LVec3>(m_properties.at("Color"));
}

void GLightComponent::SetColor(const Math::LVec3& c) {
    m_properties["Color"] = c;
}

// 注册到工厂
L_REGISTER_TYPE(GLightComponent);
```

#### 序列化如何工作

```cpp
// WorldSerializer.cpp
void WorldSerializer::Serialize(GObject* obj, nlohmann::json& out) {
    out["type"] = obj->GetTypeName();
    out["name"] = obj->GetObjectName();

    PropertyMap props;
    obj->GetProperties(props);

    for (auto& [key, val] : props) {
        std::visit([&](auto&& v) {
            out["properties"][key] = v;
        }, val);
    }
}

std::unique_ptr<GObject> WorldSerializer::Deserialize(const nlohmann::json& in) {
    std::string typeName = in["type"];
    auto obj = TypeRegistry::Get().Create(typeName);

    PropertyMap props;
    for (auto& [key, jval] : in["properties"].items()) {
        props[key] = ParsePropertyValue(jval);
    }
    obj->SetProperties(props);
    return obj;
}
```

#### 属性编辑器如何工作

```cpp
// PropertyModel.cpp — 不需要反射宏，直接遍历 PropertyMap
void PropertyModel::OnSelectionChanged(GObject* selected) {
    m_propertyList.clear();

    PropertyMap props;
    selected->GetProperties(props);

    for (auto& [name, val] : props) {
        PropertyEntry entry;
        entry.name = name;
        entry.type = GetValueType(val);  // variant → "bool"/"float"/"LVec3"/...
        entry.value = val;
        m_propertyList.push_back(entry);
    }

    emit dataChanged();
}
```

QML 端根据 `entry.type` 选择控件：
- `"float"` → 数字框或滑块
- `"bool"` → 复选框
- `"LVec3"` → VectorInput.qml（三个数字框）
- `"string"` → 文本框

#### 工作量对比

| | UE 风格反射 | 属性包 + 轻量基类 |
|---|---|---|
| 代码生成器 | 需要 UHT | **不需要** |
| 宏 | `UCLASS`, `UPROPERTY`, `GENERATED_BODY` | 1 个 `L_REGISTER_TYPE`（可选） |
| 每个类样板 | 3-5 行宏 + 标记 | `GetTypeName()` 1 行 + 构造函数注册属性 |
| 序列化 | 遍历反射数据 | 遍历 PropertyMap |
| 维护成本 | 高 | **极低** |

---

## 3. Platform 层

Platform 层是引擎核心与具体窗口系统之间的适配层。所有 Platform 实现都遵循 `IWindow` 接口，使得 Core 不感知底层窗口系统。

### 3.1 设计原则

- Engine Core 只依赖 `IWindow` 接口，不依赖任何具体 Platform
- 每个 Platform 实现是独立的 DLL，编译时选定
- Editor 和 Runtime 可以在不同场景链接不同 Platform

### 3.2 LuminPlatformQt.dll（当前实现）

基于 Qt 的 Platform 实现。
1. 用 `QOpenGLWidget` 创建窗口和 OpenGL Context
2. 将 Qt 的键盘/鼠标事件转换为 `InputState`
3. 管理 Qt 事件循环（供应用层调用）

```cpp
// LuminPlatformQt/Src/QtWindow.h

namespace Lumin {

class QtWindow : public QOpenGLWidget, public IWindow {
    Q_OBJECT
public:
    explicit QtWindow(const WindowDesc& desc);

    // IWindow 实现
    bool ShouldClose() const override;
    void SwapBuffers() override { context()->swapBuffers(this); }
    void PollEvents() override;
    const InputState& GetInputState() const override;
    int GetWidth() const override;
    int GetHeight() const override;
    float GetAspectRatio() const override;

protected:
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void closeEvent(QCloseEvent* e) override;

private:
    InputState m_inputState;
    bool m_shouldClose = false;
    static KeyCode MapQtKeyToEngine(int qtKey);
};

} // namespace Lumin
```

### 3.3 QtApp 辅助类

```cpp
// QtApp.h — 简单的 QApplication 包装，供 Editor 和 Runtime 使用
class QtApp {
public:
    QtApp(int argc, char** argv);
    int Exec();
    void SetupGLFormat();  // OpenGL 3.3 Core Profile 配置
};
```

---

## 4. 编辑器设计

### 4.1 编辑器状态机

```
                    ┌──────────────┐
          启动编辑器  │              │  点击 Stop
     ┌─────────────►│   Editing    │◄──────────────┐
     │              │              │               │
     │              └──────┬───────┘               │
     │                     │ 点击 Play              │
     │                     ▼                       │
     │              ┌──────────────┐    点击 Pause │
     │              │              │◄──────────┐   │
     │              │   Playing    │           │   │
     │              │   (PIE)      │───────┐   │   │
     │              │              │ 点击   │   │   │
     │              └──────┬───────┘ Pause  │   │   │
     │                     │               │   │   │
     │                     │               ▼   │   │
     │                     │        ┌──────────────┐
     │                     │        │   Paused     │
     │                     │        │              │
     │                     │        └──────┬───────┘
     │                     │        点击    │ 点击
     │                     │       Resume  │ StepFrame
     │                     │               │
     │                     ▼               │
     │              ┌──────────────┐       │
     │              │              │       │
     │              │   Playing    │◄──────┘
     │              │              │
     │              └──────────────┘
     │
     └────────── 关闭编辑器 = 退出
```

四种状态：
| 状态 | 编辑 UI | 视口内容 | 输入归属 | World 操作 |
|------|---------|---------|----------|-----------|
| **Editing** | 全部显示 | 编辑器场景 | 编辑器消费 | 编辑器 World |
| **Playing** | 部分锁定 | 游戏画面 | 全部 → 游戏 | PIE World (副本) |
| **Paused** | 部分锁定 | 冻结的游戏画面 | 编辑器可检查 | PIE World (只读) |

### 4.2 PIE 核心问题与设计

#### 问题1：修改属性后运行 PIE

用户在编辑器中修改了 Actor 的位置、材质等属性，点击 Play。PIE 必须使用最新编辑状态。

**设计：World 序列化 + 反序列化拷贝**

```
点击 Play
  │
  ├── 1. 将编辑器 World 序列化为内存 buffer（或 JSON 字符串）
  │      WorldSerializer::Serialize(editorWorld, buffer)
  │
  ├── 2. 从 buffer 反序列化创建 PIE World
  │      WorldSerializer::Deserialize(buffer, pieWorld)
  │
  ├── 3. 在 PIE World 上创建 GameInstance，开始 Tick
  │
  └── 4. Stop 时，销毁 PIE World。编辑器 World 保持不变
```

序列化是 PIE 的基石，同时也是"保存场景"和"加载场景"的基石——一次实现，三处受益。

#### 问题2：运行时修改不应污染编辑器

PIE 运行时 Actor 被移动/销毁/生成，Stop 后编辑器状态应回到 Play 前。

```
PIE 期间:
  编辑器 World: 冻结，不变    ← 放在一边
  PIE World:    Tick，变化    ← 所有运行时操作在这里

Stop:
  PIE World:    直接丢弃
  编辑器 World: 恢复，编辑 UI 重新指向它
```

#### 问题3：编辑器专用对象不应进入游戏

编辑器有自己的 Actor（Gizmo、网格线、编辑器相机），这些不应该被拷贝到 PIE World。

```cpp
class GActor {
public:
    // 编辑器专用标记，序列化时跳过
    bool IsEditorOnly() const { return m_editorOnly; }
    void SetEditorOnly(bool v) { m_editorOnly = v; }

private:
    bool m_editorOnly = false;
};
```

WorldSerializer 序列化时自动跳过 `m_editorOnly == true` 的 Actor。

#### 问题4：运行时日志如何查看

PIE 运行期间，Game.dll 中的 Log 需要显示在编辑器控制台。

```cpp
// LLog 支持回调，编辑器注册回调将日志转发到 QML LogModel
class LLog {
public:
    using LogCallback = std::function<void(LogLevel, const char*, const char*)>;
    static void AddCallback(LogCallback cb);
};

// 编辑器中
LLog::AddCallback([this](LogLevel lv, const char* category, const char* msg) {
    m_logModel->Append(lv, category, msg);  // 自动刷新 QML 列表
});
```

#### 问题5：Game.dll 热重载

作为独立开发者，这是迭代速度的关键。修改 C++ 代码 → 编译 Game.dll → 编辑器内点击"Reload" → 无需重启编辑器。

```
Reload Game.dll 流程:
  │
  ├── 1. 如果正在 PIE，先 StopPIE
  ├── 2. FreeLibrary(旧 Game.dll)
  ├── 3. 等待编译完成（文件监控 or 手动触发）
  ├── 4. LoadLibrary(新 Game.dll)
  ├── 5. CreateGameModule() → 新的 GameInstance
  ├── 6. 重建 GameInstance → 初始化 → 关联编辑器 World
  └── 7. 编辑器状态完全恢复
```

实现要点：
- 热重载前后编辑器 World 不受影响（World 属于引擎，不属于 Game.dll）
- 如果编辑器检测到 Game.dll 文件变化，工具栏显示"Reload"按钮高亮
- 热重载失败（编译错误）时，保持旧的 Game.dll 继续运行，控制台打印错误

#### 问题6：属性编辑器

属性编辑器通过 `GObject::GetProperties()` 获取 PropertyMap，遍历显示。不需要反射宏。

```cpp
// 选中的对象
GObject* selected = m_selection->GetSelected();

// 获取属性
PropertyMap props;
selected->GetProperties(props);

// 遍历 → QML ListView 显示
// props 中每个 entry 有 name + type + value
// QML 根据 type 选择控件（VectorInput / 滑块 / 复选框 / 文本框）
```

属性编辑器和序列化**共用同一份 PropertyMap**，属性编辑器改了什么，序列化就存什么。不会出现两边不一致的问题。

### 4.3 编辑器 Tick 循环

```
每帧 Tick:
  │
  ├── m_window->PollEvents()           // Qt 事件 + 更新 InputState
  │
  ├── if (m_state == Playing || Paused):
  │   │
  │   ├── if (Playing):
  │   │     m_pieGameInstance->Tick(dt)  // 游戏逻辑
  │   │
  │   ├── 渲染 PIE World 到视口
  │   │
  │   └── if (Paused):
  │         // 不 Tick 游戏逻辑，但保持渲染
  │         // StepFrame: 单帧 Tick 后再冻结
  │
  ├── else (Editing):
  │   │
  │   ├── m_editorWorld.Tick(dt)        // 编辑器 World（通常不做逻辑，仅渲染）
  │   ├── m_gizmo->Update()
  │   ├── m_selection->Update()
  │   ├── 渲染编辑器 World + Gizmo + 网格等
  │   │
  │   └── QML UI 保持响应
  │
  └── m_window->SwapBuffers()
```

### 4.4 编辑器项目结构

```
LuminEditor/
├── Src/
│   ├── Main.cpp                     # 入口
│   ├── EditorApp.h/cpp              # 编辑器应用，加载 QML
│   ├── EditorEngine.h/cpp           # 状态机 + Tick 控制
│   │
│   ├── Backend/                     # C++ 后端（暴露给 QML）
│   │   ├── SceneModel.h/cpp         # 场景大纲 (QAbstractListModel)
│   │   ├── PropertyModel.h/cpp      # 属性编辑器模型
│   │   ├── AssetModel.h/cpp         # 资源列表模型
│   │   ├── LogModel.h/cpp           # 日志模型
│   │   ├── EditorCommands.h/cpp     # 编辑器命令 (Q_INVOKABLE)
│   │   └── ViewportController.h/cpp # 视口交互（编辑器相机、选中射线）
│   │
│   ├── EditorActions/               # 编辑器操作（不依赖 Qt）
│   │   ├── UndoRedo.h/cpp           # 撤销/重做系统
│   │   ├── Gizmo.h/cpp              # 变换 Gizmo（平移/旋转/缩放）
│   │   ├── Selection.h/cpp          # 选中管理（单选/框选）
│   │   └── EditorCamera.h/cpp       # 编辑器自由相机（WASD飞行）
│   │
│   ├── Asset/                       # 资产管理
│   │   ├── AssetRegistry.h/cpp      # 资源注册表
│   │   ├── AssetImporter.h/cpp      # 资源导入 (fbx→.lmesh 等)
│   │   └── AssetThumbnail.h/cpp     # 缩略图生成
│   │
│   ├── HotReload/                   # 热重载
│   │   └── GameDLLWatcher.h/cpp     # Game.dll 文件监控 + 重载
│   │
│   └── Packaging/                   # 打包
│       └── ProjectPacker.h/cpp
│
├── Resources/
│   └── QML/
│       ├── MainWindow.qml
│       ├── ViewportPanel.qml
│       ├── SceneOutliner.qml
│       ├── PropertyEditor.qml
│       ├── AssetBrowser.qml
│       ├── ConsolePanel.qml
│       ├── Toolbar.qml
│       ├── MenuBar.qml
│       └── Components/
│           ├── VectorInput.qml
│           ├── ColorPicker.qml
│           └── AssetPreview.qml
│
└── CMakeLists.txt / .vcxproj
    └── Qt 模块: Core, Gui, Quick, QuickControls2, OpenGL
```

### 4.5 编辑器入口与 QML 绑定

```cpp
// LuminEditor/Src/Main.cpp
int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    Lumin::QtApp::SetupGLFormat();

    Lumin::EditorEngine editorEngine;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("editorEngine", &editorEngine);
    engine.rootContext()->setContextProperty("sceneModel", editorEngine.GetSceneModel());
    engine.rootContext()->setContextProperty("propertyModel", editorEngine.GetPropertyModel());
    engine.rootContext()->setContextProperty("assetModel", editorEngine.GetAssetModel());
    engine.rootContext()->setContextProperty("logModel", editorEngine.GetLogModel());

    engine.load("qrc:/QML/MainWindow.qml");
    return app.exec();
}
```

```cpp
// EditorEngine.h — 核心类
class EditorEngine : public QObject {
    Q_OBJECT

    // 暴露给 QML 的状态
    Q_PROPERTY(EditorState currentState READ GetState NOTIFY stateChanged)

public:
    enum class EditorState { Editing, Playing, Paused };

    // QML 可调用的槽
    Q_INVOKABLE void Play();
    Q_INVOKABLE void Stop();
    Q_INVOKABLE void Pause();
    Q_INVOKABLE void StepFrame();
    Q_INVOKABLE void ReloadGameDLL();

    // 每帧由 Qt 定时器驱动
    void OnTick();

    // 模型访问
    SceneModel*    GetSceneModel()    { return &m_sceneModel; }
    PropertyModel* GetPropertyModel() { return &m_propertyModel; }
    AssetModel*    GetAssetModel()    { return &m_assetModel; }
    LogModel*      GetLogModel()      { return &m_logModel; }

signals:
    void stateChanged(EditorState state);

private:
    EditorState m_state = EditorState::Editing;

    // 编辑器拥有: 编辑用的 World
    GWorld m_editorWorld;

    // PIE 拥有: 游戏运行时 World (Stop 时销毁)
    std::unique_ptr<GWorld> m_pieWorld;
    std::unique_ptr<LGameInstanceBase> m_pieGameInstance;

    // 编辑器子系统
    std::unique_ptr<EditorCamera> m_editorCamera;
    std::unique_ptr<Gizmo> m_gizmo;
    std::unique_ptr<Selection> m_selection;
    std::unique_ptr<UndoRedo> m_undoRedo;

    // 模型
    SceneModel    m_sceneModel;
    PropertyModel m_propertyModel;
    AssetModel    m_assetModel;
    LogModel      m_logModel;

    // 热重载
    std::unique_ptr<GameDLLWatcher> m_hotReload;

    void EnterPIE();
    void ExitPIE();
};
```

---

## 5. LuminRuntime.exe — 游戏独立启动器

### 5.1 职责

LuminRuntime.exe 用于两种场景：
1. **开发期**：命令行启动 `LuminRuntime run MyProject`
2. **发布后**：打包目录中的游戏入口

### 5.2 打包后的游戏目录结构

```
MyGame/
├── MyGame.exe                       # = LuminRuntime.exe 重命名
├── MyGame.dll                       # 用户游戏逻辑
├── LuminEngine.dll                  # 引擎核心
├── LuminPlatformQt.dll              # Qt 平台层
├── Qt6Core.dll, Qt6Gui.dll, ...     # Qt 运行时 DLL
├── Assets/                          # 烘焙后的游戏资源
│   ├── Meshes/
│   ├── Textures/
│   ├── Materials/
│   └── Shaders/
├── project.luproject
└── standalone.flag                  # 标记为独立游戏，跳过命令行
```

### 5.3 Runtime 与 Editor 的关系

```
开发阶段:

  程序员                 设计师                玩家
    │                      │                    │
    ▼                      ▼                    │
  LuminEditor.exe ←── LuminEditor.exe           │
  写代码/调试         编辑场景/资产             │
    │                      │                    │
    │              ┌───────┴───────┐            │
    │              │   PIE 测试    │            │
    │              └───────────────┘            │
    │                      │                    │
    └──────────┬───────────┘                    │
               │ 打包                            │
               ▼                                │
        ProjectPacker                           │
        烘焙资源 + 收集DLL                       │
               │                                │
               ▼                                │
         打包产物 ──────────────────────────────►│
                                          双击运行游戏
```

---

## 6. 打包系统 (Packaging)

### 6.1 打包流程

```
编辑器: File → Package Project → 打包
  │
  ├── Step 1: 资源烘焙 (Cook)
  │   ├── 纹理 → 压缩为 .ltex (GPU 友好格式)
  │   ├── 模型 → 转为 .lmesh (去除原始文件开销)
  │   ├── Shader → 预编译/缓存
  │   └── 其他资产 → 序列化为二进制
  │
  ├── Step 2: 收集依赖
  │   ├── Game.dll
  │   ├── LuminEngine.dll
  │   ├── LuminPlatformQt.dll
  │   ├── Qt 运行时 DLL (Qt6Core, Qt6Gui, Qt6Quick, Qt6OpenGL...)
  │   └── VC++ Redist
  │
  ├── Step 3: 复制 LuminRuntime.exe → 重命名为 <项目名>.exe
  │
  └── Step 4: 写入 standalone.flag
```

### 6.2 打包后的启动逻辑

```cpp
// LuminRuntime/Src/Main.cpp
int main(int argc, char* argv[]) {
    if (LProjectTool::IsStandalonePackage()) {
        RunStandalone();
        return 0;
    }

    Lumin::QtApp app(argc, argv);
    Lumin::InitLog();
    auto cmd = EngineRuntime::LCommandLine::Parse(argc, argv);
    return cmd.Dispatch();
}
```

---

## 7. 实施路线

### Phase 1: 自研数学库 + 替换
- 实现 `LVec2/3/4`、`LMat3/4`、`LQuat`、`LTransform`
- 全局替换所有 `QVector2D/3D`、`QQuaternion`、`QMatrix4x4`
- 重写 `Common.h` 中的 `LTransform`、`CameraInfo`、`LightInfo`
- 移除 `EngineMath/`（废弃代码）
- **目标：Core 中不再 include 任何 Qt 数学类型**

### Phase 2: OpenGL 去 Qt 化
- 引入 GLAD
- 移除 `LOpenGLFunctionsManager`（GLAD 不需要单例管理）
- `LShader`、`LTexture`、`LVertexLayout` 不再继承 Qt GL 类
- **目标：OpenGL 调用全部通过 GLAD**

### Phase 3: 基础设施去 Qt 化
- `LLog` → 纯 C++ + 回调机制（为编辑器控制台做准备）
- `LFileSystem` → `std::filesystem`，`QByteArray` → `std::vector<uint8_t>`
- `LMaterial` → nlohmann/json
- `LTexture` 图片加载 → stb_image
- `LInputManager` → 纯数据 `InputState`
- **目标：LuminCore 零 Qt include**

### Phase 4: 提取 Platform 层 + 属性系统
- 定义 `IWindow` 接口和 `InputState` 结构
- 创建 `LuminPlatformQt` 项目
- `LViewport` 重构为 `QtWindow : IWindow`，`LEngine` 接受 `IWindow*`
- 实现 `PropertyValue`（std::variant）+ `GObject` 序列化接口
- 实现 `TypeRegistry`（类型工厂） + `L_REGISTER_TYPE` 宏
- 实现 `WorldSerializer`（基于 PropertyMap，用于 PIE + 保存/加载）
- **目标：Core 通过接口使用窗口，World 可序列化，属性系统就位**

### Phase 5: 编辑器开发 (Qt Quick)
- 创建 `LuminEditor` 项目（Qt Quick + QML）
- 编辑器主窗口 + 面板布局
- ViewportPanel（嵌入 QOpenGLWidget）
- 场景大纲 + 属性编辑器（基于反射系统）
- 资源浏览器 + 控制台（Log 回调）
- 选择 / Gizmo / 编辑器相机
- 撤销/重做
- **目标：可在编辑器中编辑场景**

### Phase 6: PIE + 热重载
- 编辑器状态机（Editing / Playing / Paused）
- World 序列化拷贝启动 PIE
- 输入路由切换
- Game.dll 热重载（FreeLibrary → 编译 → LoadLibrary）
- **目标：编辑器内可运行游戏，可热重载 C++ 代码**

### Phase 7: 打包系统
- 资源烘焙（纹理、模型、Shader）
- 依赖收集 + 打包输出
- standalone.flag 独立启动
- **目标：可产出独立运行的游戏包**
