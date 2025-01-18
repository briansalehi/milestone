#pragma once

#include <memory>

#include <QObject>
#include <QTimer>
#include <QTimerEvent>

#include <EntryList.hpp>
#include <NoteModel.hpp>
#include <PracticeModel.hpp>
#include <BoxModel.hpp>
#include <flashback/flashback.hpp>
#include <flashback/subject.hpp>
#include <flashback/topic.hpp>
#include <flashback/practice.hpp>
#include <flashback/resource.hpp>
#include <flashback/section.hpp>
#include <flashback/note.hpp>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    virtual ~Database() override;

    Q_INVOKABLE EntryList* subjects();
    Q_INVOKABLE EntryList* topics(std::uint64_t const subject_id);
    Q_INVOKABLE PracticeModel* practices(std::uint64_t const topic_id);
    Q_INVOKABLE EntryList* resources();
    Q_INVOKABLE EntryList* sections(std::uint64_t const resource_id);
    Q_INVOKABLE NoteModel* notes(std::uint64_t const section_id);
    Q_INVOKABLE void section_study_completed(std::uint64_t const section_id);
    Q_INVOKABLE BoxModel* note_blocks(std::uint64_t const note_id);
    Q_INVOKABLE BoxModel* practice_blocks(std::uint64_t const practice_id);

protected:
    std::unique_ptr<flashback::database> connect_database();

signals:
    void connectionStateChanged(bool const is_connected);

private:
    std::unique_ptr<QTimer> m_connection_timer;
};
