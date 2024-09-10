#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Database.hpp>
#include <EntryList.hpp>
#include <Entry.hpp>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Entry>("flashback.entry", 1, 0, "Entry");

    EntryList entries{};
    Entry res1{};
    res1.headline("Resource A");
    res1.lastUpdate("2 days ago");
    entries.addEntry(res1);
    Entry res2{};
    res2.headline("Resource B");
    res2.lastUpdate("47 days ago");
    entries.addEntry(res2);

    QQmlApplicationEngine engine;
    auto failure = []() { QCoreApplication::exit(-1); };
    QObject::connect( &engine, &QQmlApplicationEngine::objectCreationFailed, &app, failure, Qt::QueuedConnection);
    engine.loadFromModule("Milestone", "Main");
    engine.rootContext()->setContextProperty("entries", &entries);

    return app.exec();
}

