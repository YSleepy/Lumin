#pragma once
#include <QString>

namespace EngineRuntime
{
	class LProjectTool
	{
	public:
		static bool CreateProject(const QString& name, const QString& path);
		static QString ApplyTemplate(const QString& content, const QMap<QString, QString>& vars);
		static bool WriteFromTemplate(const QString& templatePath, const QString& outputPath, const QMap<QString, QString>& vars);
	};
}
