#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include "JuceHeader.h"
#include "Metronome.h"


int main (int argc, char* argv[])
{
    QCoreApplication::setApplicationName ("Metronome");
    QCoreApplication::setOrganizationName ("witte");
    QCoreApplication::setApplicationVersion ("0.0.1");
    QCoreApplication::setOrganizationDomain ("witte.github.io");

    QCoreApplication::setAttribute (Qt::AA_EnableHighDpiScaling);
    QGuiApplication app (argc, argv);
    QQmlApplicationEngine qmlEngine;

    Metronome metronome;
    qmlEngine.rootContext()->setContextProperty ("metronome", &metronome);

    qmlEngine.load("qrc:/Main.qml");
    if (qmlEngine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
