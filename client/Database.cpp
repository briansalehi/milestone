#include <QQmlEngine>
#include <QQmlContext>
#include <QString>
#include <Database.hpp>

Database::Database(QObject *parent)
    : QObject{parent}
    , m_database{"postgresql://localhost/flashback"}
{
    for (flashback::resource const& resource: m_database.resources())
    {
        Entry entry{};
        entry.headline(QString::fromStdString(resource.name));
        entry.incompleteSections(QString::number(resource.incomplete_sections));

        if (entry.headline().size() > 0)
        {
            m_entryList.addEntry(entry);
        }
    }
}

EntryList Database::entryList() const
{
    return m_entryList;
}
