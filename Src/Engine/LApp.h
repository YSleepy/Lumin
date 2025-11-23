#pragma once
#include <QApplication>

namespace Lumin
{
	//实现应用级别的全局快捷键
	//需要全局监控应用状态变化
	class LApp : public QApplication
	{
	public:
		LApp(int argc, char** argv);
	};

}

