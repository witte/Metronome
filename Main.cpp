#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QFontDatabase>

#include "JuceHeader.h"
#include "Metronome.h"


int main (int argc, char* argv[])
{
    QCoreApplication::setOrganizationName   ("witte");
    QCoreApplication::setOrganizationDomain ("witte.github.io");
    QCoreApplication::setApplicationName    (ProjectInfo::projectName);
    QCoreApplication::setApplicationVersion (ProjectInfo::versionString);

    QCoreApplication::setAttribute (Qt::AA_EnableHighDpiScaling);
    QGuiApplication app (argc, argv);
    QQmlApplicationEngine qmlEngine;

    QFontDatabase::addApplicationFont(":/OpenSansCondensed-Light.ttf");
    app.setFont({"Open Sans Condensed Light"});

    Metronome metronome;
    qmlEngine.rootContext()->setContextProperty ("metronome", &metronome);

    qmlEngine.load("qrc:/Main.qml");
    if (qmlEngine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
