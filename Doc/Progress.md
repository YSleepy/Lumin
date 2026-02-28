## 11.28: 
* `bug`: LOpenGLFunctionsManager : public QOpenGLFunctions_3_3_Core作为单例，难以控制生命周期，导致OpenGL上下文比QOpenGLFunctions_3_3_Core对象先销毁，出现断言。
* `debug`: 使用指针+手动销毁，在LViewport销毁前，销毁实例。

## 11.28:
* `issue`: log中无法判断所在线程以及其他信息
* `commit`: 临时添加customMessageHandler

## 11.29
* `issue`: 图形绘制
* `commit`: 使用简单着色器程序绘制简单图案
* `tip`: glClear在绘制前调用，否则

## 11.30
* `bug`: 逻辑线程与渲染线程的同步问题，先作为`遗留`
* `debug`: ,预留解决方案：生产消费问题

## 11.30
* `issue`: 添加移动控制
* `commit`: 在Example中添加移动控制。

## 11.30
* `design`: 概念引入GamePlay FrameWork，设计阶段
* `point`: 参考虚幻引擎GamePlay

## 12.01~12.03
* `design`: 概念引入GamePlay FrameWork，编码阶段
* `point`: 参考虚幻引擎GamePlay

## 12.06
* `issue`: 由矩阵变换控制Actor移动
* `commit`: 定义模型矩阵，更改RenderObj为RenderCmd，添加相关逻辑

## 12.07
* `bug`: Render相关逻辑不应当使用GamePlay内容
* `debug`重构LMeshSceneComponent

## 12.08
* `design`: 场景组件和逻辑组件应当分离，暂时作为`遗留`
* `point`:

## 12.08
* `design`: 摄像机组件，视图矩阵（相机变换逆矩阵）
* `point`: 了解3D矩阵，设计并编写

## 12.10
* `issue`: 添加玩家控制器，优化玩家输入
* `commit`: 键盘`遗留`和鼠标通过掩码设计保存

## 12.11~12.14
* `issue`: 由于引擎有两个线程循环，日志在控制台无法清晰阅读，需要将日志落盘
* `commit`: 更新日志落盘功能
* `commit`: 更新摄像机组件，添加玩家控制器（参考UE）

## 12.14
* `bug`: 欧拉角引入的万向锁问题
* `debug`: 使用四元数规避相关问题

## 12.24
* `bug`: 纹理透明通道显示问题
* `debug`: 启用混合，设置混合函数

## 12.24
* `bug`: 纹理倒立
* `debug`: Qt 与 OpenGL 的原点不同

| 系统            | 原点        |
| ------------- | --------- |
| **QImage**    | 左上角 (0,0) |
| **OpenGL UV** | 左下角 (0,0) |

## 12.26
* `bug`: string 遗留问题，引擎最开始编码使用的是string，可引擎使用大量qt类，不可避免的出现类型转换
* `debug`: 继续遗留，改动太多，以后再说

## 12.30
* `bug`: gltf使用tinygltf::TinyGLTF::LoadASCIIFromFile时间开销极大
* `debug`: 仿照虚幻引擎提供一种二进制资源文件（适应OpenGL的格式，加载方便），这样只有在导入时缓慢
* `debug`: 暂时没考虑好各种二进制文件如何保存，先做遗留

## 1.01
* `bug`: 设计缺陷：摄像机和Pawn不应该绑定，不应该从默认Pawn中获取相机数据
* `debug`: 分离为 默认相机和Pawn两个类，或者默认使用Pawn下的摄像机，如果没有，则自动创建一个
* `debug`: 运行PlayerController指定相机对象

## 1.02
* `bug`: 解决遗留问题，`12.08`
* `bugDescription` : 根据虚幻引擎设计结构应当如此，在实现gltf模型导入是遇到相关问题
* `debug`: 虚幻引擎提供导入时是否合并模型的功能，这里将暂时不提供合并能力，所以需要场景组件描述
           mesh的位置关系
