#include <thread>
#include <QThread>
#include <QDateTime>
#include <filesystem>

#include "Engine/LApp.h"
#include "Example/EGameInstance.h"
#include "Engine/LEngine.h"
// 自定义消息处理器（线程ID十进制显示）
void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	quintptr threadId = reinterpret_cast<quintptr>(QThread::currentThreadId());
	QString threadIdStr = QString::number(threadId);

	const char* typeStr = nullptr;
	switch (type) {
	case QtDebugMsg:     typeStr = "DEBUG";     break;
	case QtWarningMsg:   typeStr = "WARNING";   break;
	case QtCriticalMsg:  typeStr = "CRITICAL";  break;
	case QtFatalMsg:     typeStr = "FATAL";     break;
	case QtInfoMsg:      typeStr = "INFO";      break;
	default:             typeStr = "UNKNOWN";
	}

	QString log = QString("[%1] [线程ID:%2] [%3] %4 (文件:%5, 行:%6)")
		.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
		.arg(threadIdStr) // 十进制线程ID
		.arg(typeStr)
		.arg(msg)
		.arg(context.file ? std::filesystem::path(context.file).filename().string().c_str() : "未知文件")
		.arg(context.line);

	fprintf(stderr, "%s\n", log.toLocal8Bit().constData());

	// 致命错误需终止程序
	if (type == QtFatalMsg) abort();
}

int main(int argc, char *argv[])
{
	Lumin::LApp app(argc, argv);
	qInstallMessageHandler(customMessageHandler);
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setVersion(3, 3);  // 设置 OpenGL 版本
	format.setProfile(QSurfaceFormat::CoreProfile);  // 核心模式
	QSurfaceFormat::setDefaultFormat(format);

	qDebug() << "Main Thread";
	Lumin::LEngine& engine = Lumin::LEngine::GetInstance();
	EGameInstance* gameInstance = new EGameInstance();
	engine.SetGameInstance(gameInstance);
	Lumin::LEngineConfig engineConfig{
		{
			1080,
			960
		}
	};
	if (engine.Init(engineConfig))
	{
		std::thread engineThread(
			[&engine]()
			{
				engine.Run();//Run内有游戏主循环
			}
		);
		app.exec();
		engineThread.join();
		engine.Destroy();
	}
	return 0;
}
