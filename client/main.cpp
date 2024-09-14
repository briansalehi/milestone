#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Database.hpp>
#include <EntryList.hpp>
#include <Entry.hpp>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<EntryList>("Flashback.EntryList", 1, 0, "EntryList");
    qmlRegisterType<Entry>("Flashback.Entry", 1, 0, "Entry");

    Database database{};
    EntryList entryList{database.entryList()};

    QQmlApplicationEngine engine;
    auto failure = []() { QCoreApplication::exit(-1); };
    QObject::connect( &engine, &QQmlApplicationEngine::objectCreationFailed, &app, failure, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("entries", &entryList);
    engine.loadFromModule("Milestone", "Main");

    return app.exec();
}

