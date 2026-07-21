#pragma once
#include "pre.h"

#include <filesystem>
#include <QDateTime>
#include <QThread>

#include "QDebug"

#ifndef LOG_TAG
#define LOG_TAG "Common"
#endif

namespace Lumin
{
#define CHECK_PTR_RETURN(ptr, fmt, ...)\
	do{\
		if (!(ptr)){\
			qCritical() << "[" << LOG_TAG << "] " << QString::asprintf((fmt), ##__VA_ARGS__);\
			return;\
		}\
	}while(0)\

#define CHECK_PTR_RETURN_VALUE(ptr, value, fmt, ...)\
	do{\
		if (!(ptr)){\
			qCritical() << "["  << LOG_TAG << "] " << QString::asprintf((fmt), ##__VA_ARGS__);\
			return (value);\
		}\
	}while(0)\

#define CHECK_CONDITION_RETURN(condition, fmt, ...)\
	do{\
		if (!(condition)){\
			qCritical() << "["  << LOG_TAG << "] " << QString::asprintf((fmt), ##__VA_ARGS__);\
			return;\
		}\
	}while(0)\

#define CHECK_CONDITION_RETURN_VALUE(ptr, value, fmt, ...)\
	do{\
		if (!(ptr)){\
			qCritical() << "["  << LOG_TAG << "] " << QString::asprintf((fmt), ##__VA_ARGS__);\
			return (value);\
		}\
	}while(0)\


	// 自定义消息处理器（线程ID十进制显示）
	void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

	void ENGINE_API InitLog();
}
