#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "media/mediamanager.h"
#include "time/timeutils.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    app.setApplicationName("Media Player");
    app.setApplicationVersion("0.1.0");
    app.setOrganizationDomain("PXM");

    QQmlApplicationEngine engine;

    qmlRegisterType<TimeUtils>("Utils", 1, 0, "TimeUtils");

    MediaManager *mediaManager = MediaManager::getInstance();
    engine.rootContext()->setContextProperty("mediaManager", mediaManager);

    const QUrl url(QStringLiteral("qrc:/gui/main.qml"));
    QQuickStyle::setStyle("Material");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
