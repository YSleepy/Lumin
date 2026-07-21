# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Run

- **Open solution:** `Lumin.sln` in Visual Studio 2022
- **Toolchain:** MSVC v142 (VS2019), C++17, Qt 6.5.3_msvc2019_64
- **Platform:** x64 only
- **Configurations:** Debug and Release
- **Build:** Open in VS, build solution (LuminRuntime depends on LuminCore)
- **No CLI build or test suite exists** — this is a learning project without automated builds or tests

## Architecture: Module Split

| Module | Output | Qt | Role |
|--------|--------|-----|------|
| `LuminEngine/` | `LuminEngine.dll` | **无** | 引擎核心（纯 C++） |
| `LuminPlatformQt/` | `LuminPlatformQt.dll` | 有 | Qt 平台实现（当前） |
| `LuminEditor/` | `LuminEditor.exe` | 有 | Qt Quick 编辑器 |
| `LuminRuntime/` | `LuminRuntime.exe` | 有 | 游戏独立启动器 |
| Game project | `Game.dll` | 仅通过引擎 | 用户游戏逻辑 |

`LuminEngine` exports via `ENGINE_API` macro (defined in `Src/Engine/pre.h` — `__declspec(dllexport)` when `ENGINECORE_EXPORTS` is defined, otherwise `__declspec(dllimport)`).

See `Doc/Lumin架构设计.md` for full architecture design.

## Engine Core (`LuminEngine`)

**Entry point / Lifecycle:**

`LEngine` is a singleton. The runtime calls `GetInstance()` → `SetGameInstance()` → `Init(config)` → `Run()` (blocking game loop) → `Destroy()`. `LEngine` uses the Pimpl idiom internally. Engine no longer creates the window — it receives an `IWindow*` from the platform layer.

**GamePlay Framework** (Unreal-inspired, under `Src/Engine/GamePlay/`):

Hierarchy: `GWorld` → `GLevel` → `GActor` → `GComponent`

- `GWorld` — owns levels, provides tick, collects lights
- `GLevel` — owns actors array, factory methods (`CreateActor<T>()`), holds `GGameModeBase`
- `GActor` — named, transformable node in a tree (parent/children), owns components. Components retrieved via `GetComponent<T>()` / `GetComponentByName<T>()` with `dynamic_cast`
- `GComponent` — abstract base with `Tick()`, owned by an actor
  - `GSceneComponent` — has a transform (position/rotation/scale). Subclassed by `GMeshSceneComponent`, `GCameraComponent`, `GLightComponent`
  - `GNonSceneComponent` — no transform, for pure-logic components
- `GGameModeBase` — holds `defaultActor` and `defaultController` pointers
- `GPlayerController` — handles mouse/keyboard input, sensitivity/speed, tick-based

**Rendering pipeline:**

`LViewport` (`Src/Engine/LViewport.h`) is a `QOpenGLWidget` subclass. It receives Qt input events and forwards them to `LInputManager`. Its `paintGL()` drives the render loop.

`LRenderQueue` — thread-safe (mutex-protected) queue of `RenderCmd` structs (mesh + material + model matrix). Game thread calls `Submit()`, render thread calls `Draw()`.

`LGraphicsCore` — thin wrapper around OpenGL calls for creating/binding shaders, VBOs/EBOs, meshes, and materials.

**OpenGL access:**
`LOpenGLFunctionsManager` is a singleton inheriting `QOpenGLFunctions_3_3_Core`. Accessed everywhere via the `L_GL` macro. Must be manually destroyed before the OpenGL context is lost (see `Doc/User/Progress.md` 11.28 bug note).

**Other subsystems:**
- `LInputManager` — keyboard (256 keys) and mouse button state, accessible via `LEngine::GetInputManager()`
- `LFileSystem` — resolves engine asset paths and game root paths
- `LGltfUtils` — glTF model loading via tinygltf (in `ThirdParty/tiny_gltf/`)
- `LLog` — logging to file (not just console)
- `EngineMath/` — custom `LVec2`, `LVec3`, `LVec4`, `LMat4`, `LQuat` in `Lumin::Math` namespace. See `IMPLEMENTATION_GUIDE.md` for details.

## Engine Runtime (`LuminRuntime`)

**Entry point:** `Src/Main.cpp` — creates `LApp`, initializes log, parses CLI, dispatches.

**Command line system** (`Src/CommandLine/`):
- `LCommandLine::Parse()` tokenizes arguments, then `Dispatch()` runs the matched command
- Commands implement `LCommand` interface: `GetName()`, `GetDescription()`, `Execute(args)`
- Built-in commands: `HelpCommand`, `CreateProjectCommand`, `RunProjectCommand`

**Project loading** (`Src/Loader/`):
- `LProjectLoader` loads a `.luproject` file, then calls `LoadLibrary` on the game DLL
- Expects DLL exports: `CreateGameModule()` → `LGameModuleBase*` and `DestroyGameModule(LGameModuleBase*)`
- `LProjectTool` generates new projects from templates in `Src/Templates/`
- `RunEngineWithProject()` wires everything together: creates engine, loads game module, spawns engine loop on a background thread, runs Qt event loop on main thread

**Default game mode** (`Src/Example/`):
- Built-in example with `EGameModule`, `EGameInstance`, `EActor` — used when no project is loaded

## Game Projects (Game.dll)

Users create projects with `LuminRuntime new <name>`, which generates a CMake project from templates. The game DLL must export:
- `LGameModuleBase* CreateGameModule()` — returns a subclass of `LGameModuleBase`
- `void DestroyGameModule(LGameModuleBase*)` — cleans up

`LGameModuleBase::CreateGameInstance()` returns the user's `LGameInstanceBase` subclass, which owns the `GWorld` and its levels/actors.

## Coding Conventions

1. **文件名** = 文件内主类名，如 `LEngine.h` / `LEngine.cpp`
2. **类名、函数名** — 大驼峰 (PascalCase)，如 `GetWorldPosition()`
3. **引擎类前缀** `L` — `LEngine`, `LShader`, `LMesh`, `LInputManager`, `LRenderQueue`
4. **GamePlay 框架类前缀** `G` — `GActor`, `GWorld`, `GLevel`, `GComponent`, `GPlayerController`
5. **常量/宏** — 全大写+下划线，如 `MAX_KEYS`, `ENGINE_API`, `ENGINECORE_EXPORTS`
6. **成员变量** — 前缀 `m_`，如 `m_objectId`, `m_components`, `m_gameInstance`
7. **静态函数** — 前缀 `Static_`，如 `Static_Zero()`, `Static_One()`

**Namespaces:** `Lumin` for engine classes, `Lumin::Math` for math types, `EngineRuntime` for runtime.

## Key Conventions

- Header-only structures where possible; `.cpp` for non-trivial implementations
- `EngineMath/` is being rewritten as pure C++ (no Qt dependency) — see `IMPLEMENTATION_GUIDE.md`
- Thread separation: game logic ticks on one thread, OpenGL rendering on another, synchronized via `LRenderQueue`'s mutex
