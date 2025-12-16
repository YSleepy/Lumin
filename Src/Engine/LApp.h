#pragma once
#include <QApplication>
#include "pre.h"

namespace Lumin
{
	//实现应用级别的全局快捷键
	//需要全局监控应用状态变化
	class ENGINE_API LApp : public QApplication
	{
	public:
		LApp(int argc, char** argv);
	};

}

