#include "LLog.h"

#include <QMutex>
#include <QCoreApplication>
#include <QFile>
#include <QDir>

namespace Lumin
{
	static QMutex g_logMutex;
	void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
	{
		QMutexLocker locker(&g_logMutex);
		QString logDir = QCoreApplication::applicationDirPath() + "/Logs";
		QString logFilePath;
		QDir().mkpath(logDir);
#ifdef QT_DEBUG
		logFilePath = logDir + "/debug.log";
#else
		logFilePath = logDir + "/release.log";
#endif
		QFile file(logFilePath);
		QIODevice::OpenMode openMode = QIODevice::WriteOnly | QIODevice::Text;
		static bool isFirstLog = true;
		if (isFirstLog) {
			openMode |= QIODevice::Truncate;
			isFirstLog = false;
		}
		else {
			openMode |= QIODevice::Append;
		}
		if (!file.open(openMode))
			return;
		QTextStream out(&file);

		quintptr threadId = reinterpret_cast<quintptr>(QThread::currentThreadId());
		QString threadIdStr = QString::number(threadId);

		const char* typeStr = nullptr;
		switch (type) {
		case QtDebugMsg:     typeStr = "DEBUG";     break;
		case QtWarningMsg:   typeStr = "WARNING";   break;
		case QtCriticalMsg:  typeStr = "ERROR";  break;
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
		out << log << "\n";
		fprintf(stderr, "%s\n", log.toLocal8Bit().constData());

		// 致命错误需终止程序
		if (type == QtFatalMsg) abort();
	}

	void InitLog()
	{
		qInstallMessageHandler(customMessageHandler);
	}
}
