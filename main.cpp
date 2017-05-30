#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "viewmodel.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    ViewModel viewModel;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("viewModel",&viewModel);
    engine.load(QUrl(QLatin1String("qrc:/SelectView.qml")));
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.load(QUrl(QLatin1String("qrc:/ConfirmView.qml")));

    return app.exec();
}
