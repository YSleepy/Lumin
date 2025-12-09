|  特性   | C++11/14 写法  | C++17 推荐写法|
|  ----  | ----  |
| 类型特性判断  | std::is_integral<T>::value | std::is_integral_v<T>（_v 变量模板）
| enable_if 简化  | typename std::enable_if<...>::type |std::enable_if_t<...>（C++14 已支持，C++17 普及）
| 编译期条件分支  | 多个 enable_if 重载 |constexpr if（直接在函数内分支）
