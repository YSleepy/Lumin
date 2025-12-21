|  特性   | C++11/14 写法  | C++17 推荐写法|
|  ----  | ----  |
| 类型特性判断  | std::is_integral<T>::value | std::is_integral_v<T>（_v 变量模板）
| enable_if 简化  | typename std::enable_if<...>::type |std::enable_if_t<...>（C++14 已支持，C++17 普及）
| 编译期条件分支  | 多个 enable_if 重载 |constexpr if（直接在函数内分支）

-----------------
若需隐藏 LMaterial 实现（PIMPL 模式）
若不想对外暴露 LMaterial 的完整定义（仅暴露接口），可将 shared_ptr 的析构 / 构造逻辑限制在 DLL 内部：
```C++
// 对外头文件（MyDll.h）
#pragma once
#include <memory>
#include <functional>

// 仅声明 LMaterial（不完整类型）
class LMaterial; 

class MYDLL_API MyDllClass {
public:
    MyDllClass(); // 构造函数声明（实现放在 DLL 源文件中）
    ~MyDllClass(); // 析构函数声明（必须显式定义，不能默认）
    // 禁止拷贝（避免跨模块拷贝 shared_ptr 触发析构）
    MyDllClass(const MyDllClass&) = delete;
    MyDllClass& operator=(const MyDllClass&) = delete;

private:
    std::shared_ptr<LMaterial> m_material; // 声明时不报错
};

// DLL 源文件（MyDll.cpp）
#include "MyDll.h"
#include "LMaterialImpl.h" // 此处包含 LMaterial 的完整定义

// 构造函数：在完整类型可见的地方初始化 shared_ptr
MyDllClass::MyDllClass() : m_material(std::make_shared<LMaterial>()) {}

// 析构函数：在完整类型可见的地方定义
MyDllClass::~MyDllClass() = default;
```
