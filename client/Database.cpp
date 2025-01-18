#include <chrono>
#include <stdexcept>

#include <QString>
#include <QDebug>

#include <Database.hpp>

static constexpr std::chrono::seconds connection_retry_interval{1};

Database::Database(QObject *parent)
    : QObject{parent}
    , m_connection_timer{std::make_unique<QTimer>()}
{
    connect(m_connection_timer.get(), &QTimer::timeout, this, &Database::connect_database);

    emit connectionStateChanged(false);
    m_connection_timer->start(connection_retry_interval);
}

Database::~Database()
{

}

EntryList* Database::subjects()
{
    EntryList* subjects{new EntryList{}};

    try
    {
        std::unique_ptr<flashback::database> database{connect_database()};

        if (database != nullptr)
        {
            for (flashback::subject const& subject: database->subjects())
            {
                subjects->addEntry(Entry{subject.id, QString::fromStdString(subject.name), QString::number(subject.topics.size())});
            }
        }
    }
    catch (pqxx::broken_connection const&)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }

    return subjects;
}

EntryList *Database::topics(std::uint64_t const subject_id)
{
    EntryList* topics{new EntryList{}};

    try
    {
        std::unique_ptr<flashback::database> database{connect_database()};

        if (database != nullptr)
        {
            for (flashback::topic const& topic: database->topics(subject_id))
            {
                topics->addEntry(Entry{topic.id, QString::fromStdString(topic.name), QString::number(topic.practices.size())});
            }
        }
    }
    catch (pqxx::broken_connection const&)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }

    return topics;
}

PracticeModel* Database::practices(std::uint64_t const topic_id)
{
    PracticeModel* model{new PracticeModel{}};

    try
    {
        std::unique_ptr<flashback::database> database{connect_database()};

        if (database != nullptr)
        {
            for (flashback::practice const& note: database->practices(topic_id))
            {
                Practice practice_wrapper{note};
                model->addPractice(practice_wrapper);
            }
        }
    }
    catch (pqxx::broken_connection const&)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }

    return model;
}

EntryList* Database::resources()
{
    EntryList* resources{new EntryList{}};

    try
    {
        std::unique_ptr<flashback::database> database{connect_database()};

        if (database != nullptr)
        {
            for (flashback::resource const& resource: database->resources())
            {
                Entry entry{};
                entry.headline(QString::fromStdString(resource.name));
                QString completed{QString::number(resource.completed_sections)};
                QString total{QString::number(resource.sections.size())};
                entry.designator(QString{"%1/%2"}.arg(completed, total));
                entry.id(resource.id);

                if (entry.headline().size() == 0)
                {
                    qDebug() << "Empty resource entry from database";
                    continue;
                }
                resources->addEntry(entry);
            }
        }
    }
    catch (pqxx::broken_connection const&)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }

    return resources;
}

EntryList* Database::sections(uint64_t const resource_id)
{
    EntryList* sections{new EntryList{}};

    try
    {
        std::unique_ptr<flashback::database> database{connect_database()};

        if (database != nullptr)
        {
            QString section_name_pattern{QString::fromStdString(database->section_pattern(resource_id))};

            for (flashback::section const& section: database->sections(resource_id))
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
        }
    }
    catch (pqxx::broken_connection const&)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }

    return sections;
}

NoteModel* Database::notes(const uint64_t section_id)
{
    NoteModel* model{new NoteModel{}};

    try
    {
        std::unique_ptr<flashback::database> database{connect_database()};

        if (database != nullptr)
        {
            for (flashback::note const& note: database->notes(section_id))
            {
                Note note_wrapper{note};
                model->addNote(note_wrapper);
            }
        }
    }
    catch (pqxx::broken_connection const&)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }

    return model;
}

void Database::section_study_completed(const uint64_t section_id)
{
    try
    {
        std::unique_ptr<flashback::database> database{connect_database()};

        if (database != nullptr)
        {
            database->section_study_completed(section_id);
        }
    }
    catch (pqxx::broken_connection const&)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }
}

BoxModel *Database::note_blocks(const uint64_t note_id)
{
    BoxModel* model{new BoxModel{}};

    try
    {
        std::unique_ptr<flashback::database> database{connect_database()};

        if (database != nullptr)
        {
            for (flashback::block const& block: database->note_blocks(note_id))
            {
                Box box;

                box.id(block.id);
                box.position(block.position);
                box.content(QString::fromStdString(block.content));
                box.language(QString::fromStdString(block.language));
                box.last_update();

                switch (block.type)
                {
                case flashback::block_type::code: box.type("Code"); break;
                case flashback::block_type::text: box.type("Text"); break;
                default: throw std::runtime_error("block type not specified");
                }

                model->addBox(box);
            }
        }
    }
    catch (pqxx::broken_connection const&)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }

    return model;
}

BoxModel *Database::practice_blocks(const uint64_t practice_id)
{
    BoxModel* model{new BoxModel{}};

    try
    {
        std::unique_ptr<flashback::database> database{connect_database()};

        if (database != nullptr)
        {
            for (flashback::block const& block: database->practice_blocks(practice_id))
            {
                Box box;

                box.id(block.id);
                box.position(block.position);
                box.content(QString::fromStdString(block.content));
                box.language(QString::fromStdString(block.language));
                box.last_update();

                switch (block.type)
                {
                case flashback::block_type::code: box.type("Code");
                case flashback::block_type::text: box.type("Text");
                }

                model->addBox(box);
            }
        }
    }
    catch (pqxx::broken_connection const&)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }

    return model;
}

std::unique_ptr<flashback::database> Database::connect_database()
{
    std::unique_ptr<flashback::database> database{nullptr};

    try
    {
        database = std::make_unique<flashback::database>("postgresql://flashback@fsystem/flashback");

        if (m_connection_timer->isActive())
        {
            m_connection_timer->stop();
            emit connectionStateChanged(true);
        }
    }
    catch (pqxx::broken_connection const&)
    {
    }
    catch (std::exception const& exp)
    {
        qDebug() << exp.what();
    }

    if (database == nullptr)
    {
        emit connectionStateChanged(false);
        m_connection_timer->start(connection_retry_interval);
    }

    return std::move(database);
}
