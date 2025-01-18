#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Database.hpp>
#include <EntryList.hpp>
#include <Entry.hpp>
#include <NoteModel.hpp>
#include <BoxModel.hpp>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<flashback::database::connection_state>("Flashback.Database", 1, 0, "ConnectionState");
    qmlRegisterType<Database>("Flashback.Database", 1, 0, "Database");
    qmlRegisterType<EntryList>("Flashback.EntryList", 1, 0, "EntryList");
    qmlRegisterType<NoteModel>("Flashback.NoteModel", 1, 0, "NoteModel");
    qmlRegisterType<BoxModel>("Flashback.BoxModel", 1, 0, "BoxModel");
    qmlRegisterType<Note>("Flashback.Note", 1, 0, "Note");
    qmlRegisterType<Entry>("Flashback.Entry", 1, 0, "Entry");

    QQmlApplicationEngine engine;
    auto failure = []() { QCoreApplication::exit(-1); };
    QObject::connect( &engine, &QQmlApplicationEngine::objectCreationFailed, &app, failure, Qt::QueuedConnection);
    //engine.rootContext()->setContextProperty("database", &database);
    engine.loadFromModule("Milestone", "Main");

    return app.exec();
}

