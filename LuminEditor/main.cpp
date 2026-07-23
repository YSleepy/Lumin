#include <QApplication>
#include <QQmlApplicationEngine>
#include "Src/LMarkdownView.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    qmlRegisterType<LMarkdownView>("Lumin.Editor", 1, 0, "LMarkdownView");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/lumineditor/Resources/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
