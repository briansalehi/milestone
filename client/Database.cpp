#include <Database.hpp>
#include <QString>
#include <QDebug>

Database::Database(QObject *parent)
    : QObject{parent}
    , m_database{"postgresql://localhost/flashback"}
{
}

EntryList* Database::subjects()
{
    EntryList* subjects{new EntryList{}};

    for (flashback::subject const& subject: m_database.subjects())
    {
        Entry entry{};
        entry.headline(QString::fromStdString(subject.name));
        entry.designator(QString::number(subject.topics.size()));

        if (entry.headline().size() == 0)
        {
            qDebug() << "Empty subject entry from database";
            continue;
        }
        subjects->addEntry(entry);
    }

    return subjects;
}

EntryList* Database::resources()
{
    EntryList* resources{new EntryList{}};

    for (flashback::resource const& resource: m_database.resources())
    {
        Entry entry{};
        entry.headline(QString::fromStdString(resource.name));
        entry.designator(QString::number(resource.incomplete_sections));

        if (entry.headline().size() == 0)
        {
            qDebug() << "Empty resource entry from database";
            continue;
        }
        resources->addEntry(entry);
    }

    return resources;
}
