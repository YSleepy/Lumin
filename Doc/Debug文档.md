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
