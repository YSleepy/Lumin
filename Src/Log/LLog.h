#pragma once
#include "QDebug"

#ifndef LOG_TAG
#define LOG_TAG "Common"
#endif

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
