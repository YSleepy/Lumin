#include "LProjectTool.h"

#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>

#include "FileSystem/LFileSystem.h"

namespace EngineRuntime
{
	bool LProjectTool::CreateProject(const QString& name, const QString& path)
	{

		QString rootPath = QDir::fromNativeSeparators(path) + "/" + name;
		QDir dir(path);
		if (!dir.exists())
		{
			qDebug() << "Project path does not exist";
			return false;
		}
		if (!dir.mkpath(name))
		{
			qDebug() << "Failed to create project directory";
			return false;
		}

		dir.cd(name);// dir is root
		qDebug() << "Created project directory: " << dir.absolutePath();
		dir.mkpath("Source/" + name);
		dir.mkpath("Assets");
		dir.mkpath("Binaries");

		QMap<QString, QString> vars;
		vars["PROJECT_NAME"] = name;
		vars["GAME_MODULE"] = name;
		vars["ENGINE_ROOT"] = QString(Lumin::LFileSystem::GetEngineRootPath().c_str());
		vars["EXPORT_MACRO"] = name.toUpper() + "_API";
		vars["PROJECT_NAME_UPPER"] = name.toUpper();
		vars["PROJECT_PATH"] = rootPath;

		WriteFromTemplate("Templates/CMakeLists.txt.in", rootPath + "/CMakeLists.txt", vars);
		WriteFromTemplate("Templates/project.luproject.in", rootPath + "/" + name + ".luproject", vars);
		WriteFromTemplate("Templates/Source/GameModule.h.in", rootPath + "/Source/" + name + "/" + name + "GameModule.h", vars);
		WriteFromTemplate("Templates/Source/GameModule.cpp.in", rootPath + "/Source/" + name + "/" + name + "GameModule.cpp", vars);
		WriteFromTemplate("Templates/Source/GameInstance.h.in", rootPath + "/Source/" + name + "/" + name + "GameInstance.h", vars);
		WriteFromTemplate("Templates/Source/GameInstance.cpp.in", rootPath + "/Source/" + name + "/" + name + "GameInstance.cpp", vars);
		WriteFromTemplate("Templates/Source/CMakeLists.txt.in", rootPath + "/Source/" + name + "/CMakeLists.txt", vars);
		WriteFromTemplate("Templates/Source/GameExport.h.in", rootPath + "/Source/" + name + "/" + name + "Export.h", vars);
		WriteFromTemplate("Templates/Source/GameActor.h.in", rootPath + "/Source/" + name + "/" + name + "GameActor.h", vars);
		WriteFromTemplate("Templates/Source/GameActor.cpp.in", rootPath + "/Source/" + name + "/" + name + "GameActor.cpp", vars);
		return true;
	}

	QString LProjectTool::ApplyTemplate(const QString& content, const QMap<QString, QString>& vars)
	{
		QString result = content;
		for (auto it = vars.begin(); it != vars.end(); ++it)
		{
			result.replace(QString("@%1@").arg(it.key()), it.value());
		}
		return result;
	}

	bool LProjectTool::WriteFromTemplate(const QString& templatePath, const QString& outputPath,
		const QMap<QString, QString>& vars)
	{
		QFile in(templatePath);
		if (!in.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qDebug() << "Failed to open template file: " << templatePath;
			return false;
		}

		QString content = in.readAll();
		in.close();

		QString finalContent = ApplyTemplate(content, vars);

		QString path = QFileInfo(outputPath).absolutePath();
		qDebug() << "Creating directory: " << path;
		if (!QDir().mkpath(path))
		{
			qDebug() << "Failed to create directory: " << path;
			return false;
		}

		QFile out(outputPath);
		qDebug() << "Writing to file: " << outputPath;
		if (!out.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			qDebug() << "Failed to open output file: " << outputPath;
			return false;
		}
		
		out.write(finalContent.toUtf8());
		qDebug() << out.fileName() <<" : ok";
		out.close();

		return true;
	}
}

