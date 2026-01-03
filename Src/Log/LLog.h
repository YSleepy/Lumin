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
#define CHECK_PTR_RETURN(ptr, log)\
	do{\
		if (!(ptr)){\
			qDebug() << "[" << LOG_TAG << "] " << (log);\
			return;\
		}\
	}while(0)\

#define CHECK_PTR_RETURN_VALUE(ptr, value, log)\
	do{\
		if (!(ptr)){\
			qDebug() << "["  << LOG_TAG << "] " << (log);\
			return (value);\
		}\
	}while(0)\

#define CHECK_CONDITION_RETURN(condition, log)\
	do{\
		if (!(condition)){\
			qDebug() << "["  << LOG_TAG << "] " << (log);\
			return;\
		}\
	}while(0)\

#define CHECK_CONDITION_RETURN_VALUE(ptr, value, log)\
	do{\
		if (!(ptr)){\
			qDebug() << "["  << LOG_TAG << "] " << (log);\
			return (value);\
		}\
	}while(0)\

	// TODO: 待验证
#define CHECK_CONDITION_RETURN_VALUE_FMT(ptr, value, fmt, ...) \
    do { \
        if (!(ptr)) { \
            qDebug() << "[" << LOG_TAG << "] " << QString::asprintf((fmt), ##__VA_ARGS__); \
            return (value); \
        } \
    } while(0)



	// 自定义消息处理器（线程ID十进制显示）
	void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

	void ENGINE_API InitLog();
}
