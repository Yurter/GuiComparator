#include <QQuickView>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Screenshot.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app { argc, argv };

    Screenshot screenshot;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty(QLatin1String("screenshot"), &screenshot);
    engine.load(url);

    return app.exec();
}
