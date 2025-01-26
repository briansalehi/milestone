#pragma once

#include <Note.hpp>
#include <QAbstractListModel>
#include <QObject>

class NoteModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role
    {
        Index = Qt::UserRole + 1,
        Heading,
        State,
        Creation,
        LastUpdate,
        Blocks,
    };

    explicit NoteModel(QObject *parent = nullptr);

    NoteModel(NoteModel const& other);
    NoteModel& operator=(NoteModel const& other);

    NoteModel(NoteModel&& other) noexcept;
    NoteModel& operator=(NoteModel&& other) noexcept;

    int rowCount(QModelIndex const& parent) const override;

    QVariant data(QModelIndex const& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addNote(Note const& note);

private:
    std::vector<Note> m_notes;
};
