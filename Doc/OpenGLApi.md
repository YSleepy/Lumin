glVertexAttribPointer函数的参数非常多，所以我会逐一介绍它们：
```
1. 第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
2. 第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
3. 第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
4. 下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
5. 第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个GLfloat之后，我们把步长设置为3 * sizeof(GLfloat)。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子(译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节)。
6. 最后一个参数的类型是GLvoid*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
```


<p>
线程私有
OpenGL的绘制命令都是作用在当前的Context上，这个Current Context是一个线程私有（thread-local）的变量，也就是说如果我们在线程中绘制，那么需要为该线程制定一个Current Context的，当多个线程参与绘制任务时，需要原线程解绑再重新绑定新的线程。多个线程不能同时指定同一个Context为Current Context，否则会导致崩溃。

OpenGL所创建的资源, 其实对程序员可见的仅仅是ID而已, 其内容依赖于这个上下文, 因此在大型程序中的一般做法是申请一条线程专门用于绘制，创建线程时，为该绘制线程申请一个绘制上下文，一直作为Current Context，不再进行切换。所有的绘制相关的操作，都在绘制线程完成。但是如果涉及复杂的OpenGL渲染时, 这样就未必足够，当有需求需多个并行的绘制任务时，则要创建多个Context，为并行的线程分别绑定不同的上下文。
</p>

```

class SimpleOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
	Q_OBJECT

public:
	explicit SimpleOpenGLWidget(QWidget* parent = nullptr)
		: QOpenGLWidget(parent)
	{
		// 设置自动重绘定时器
		QTimer* timer = new QTimer(this);
		connect(timer, &QTimer::timeout, this, [this]() {
			update(); // 触发重绘
			});
		timer->start(16); // 约60fps
		resize(1960, 1080);  // 默认大小
		this->show();
	}

protected:
	void initializeGL() override
	{
		// 初始化OpenGL函数
		initializeOpenGLFunctions();

		// 设置清除颜色为蓝色
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

		// 启用深度测试
		glEnable(GL_DEPTH_TEST);

		qDebug() << "OpenGL initialized successfully";
		qDebug() << "OpenGL Version:" << (const char*)glGetString(GL_VERSION);
		qDebug() << "GLSL Version:" << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	}

	void resizeGL(int w, int h) override
	{
		// 设置视口
		glViewport(0, 0, w, h);
		qDebug() << "Viewport resized to:" << w << "x" << h;
	}

	void paintGL() override
	{
		static int frameCount = 0;
		frameCount++;

		// 每帧改变清除颜色以便观察
		float r = (sin(frameCount * 0.01f) + 1.0f) * 0.5f * 0.3f + 0.2f;
		float g = (cos(frameCount * 0.02f) + 1.0f) * 0.5f * 0.3f + 0.2f;
		float b = (sin(frameCount * 0.03f) + 1.0f) * 0.5f * 0.3f + 0.4f;

		glClearColor(r, g, b, 1.0f);

		// 清除颜色和深度缓冲区
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 检查OpenGL错误
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			qDebug() << "OpenGL error in frame" << frameCount << ":" << error;
		}

		// 每100帧输出一次信息
		if (frameCount % 100 == 0) {
			qDebug() << "Frame" << frameCount << "cleared with color:" << r << g << b;
		}
	}
};
#include "main.moc"
```
