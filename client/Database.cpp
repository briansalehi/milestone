#include <Database.hpp>
#include <QString>
#include <QDebug>
#include <iterator>
#include <sstream>
#include <iostream>
#include <algorithm>

Database::Database(QObject *parent)
    : QObject{parent}
    , m_database{"postgresql://flashback@localhost/flashback"}
{
}

EntryList* Database::subjects()
{
    EntryList* subjects{new EntryList{}};

    for (flashback::subject const& subject: m_database.subjects())
    {
        subjects->addEntry(Entry{subject.id, QString::fromStdString(subject.name), QString::number(subject.topics.size())});
    }

    return subjects;
}

EntryList *Database::topics(std::uint64_t const subject_id)
{
    EntryList* topics{new EntryList{}};

    for (flashback::topic const& topic: m_database.topics(subject_id))
    {
        topics->addEntry(Entry{topic.id, QString::fromStdString(topic.name), QString::number(topic.practices.size())});
    }

    return topics;
}

PracticeModel* Database::practices(std::uint64_t const topic_id)
{
    PracticeModel* model{new PracticeModel{}};

    for (flashback::practice const& note: m_database.practices(topic_id))
    {
        Practice practice_wrapper{note};
        model->addPractice(practice_wrapper);
    }

    return model;
}

EntryList* Database::resources()
{
    EntryList* resources{new EntryList{}};

    for (flashback::resource const& resource: m_database.resources())
    {
        Entry entry{};
        entry.headline(QString::fromStdString(resource.name));
        entry.designator(QString::number(resource.incomplete_sections));
        entry.designator(QString::number(resource.incomplete_sections));
        entry.id(resource.id);

        if (entry.headline().size() == 0)
        {
            qDebug() << "Empty resource entry from database";
            continue;
        }
        resources->addEntry(entry);
    }

    return resources;
}

EntryList* Database::sections(uint64_t const resource_id)
{
    EntryList* sections{new EntryList{}};

    QString section_name_pattern{QString::fromStdString(m_database.section_pattern(resource_id))};

    for (flashback::section const& section: m_database.sections(resource_id))
    {
        Entry entry{};
        entry.headline(QString{"%1 %2"}.arg(section_name_pattern).arg(section.number));

        std::string designator{};
        switch (section.state)
        {
            using state = flashback::publication_state;
        case state::open: designator = "open"; break;
        case state::writing: designator = "writing"; break;
        case state::completed: designator = "completed"; break;
        case state::revised: designator = "revised"; break;
        case state::validated: designator = "validated"; break;
        case state::approved: designator = "approved"; break;
        case state::released: designator = "released"; break;
        case state::ignored: designator = "ignored"; break;
        }
        entry.designator(QString::fromStdString(designator));
        entry.id(section.id);

        if (entry.headline().size() == 0)
        {
            qDebug() << "Empty resource entry from database";
            continue;
        }
        sections->addEntry(entry);
    }

    return sections;
}

NoteModel* Database::notes(const uint64_t section_id)
{
    NoteModel* model{new NoteModel{}};

    for (flashback::note const& note: m_database.notes(section_id))
    {
        Note note_wrapper{note};
        model->addNote(note_wrapper);
    }

    return model;
}
