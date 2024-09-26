#include "NoteModel.hpp"
#include <QByteArray>
#include <QHash>

NoteModel::NoteModel(QObject *parent)
    : QAbstractListModel{parent}
{}

NoteModel::NoteModel(const NoteModel &other)
    : m_notes(other.m_notes)
{
}

NoteModel &NoteModel::operator=(const NoteModel &other)
{
    m_notes = other.m_notes;
    return *this;
}

NoteModel::NoteModel(NoteModel &&other) noexcept
    : m_notes{std::move(other.m_notes)}
{
}

NoteModel& NoteModel::operator=(NoteModel&& other) noexcept
{
    m_notes = std::move(other.m_notes);
    return *this;
}

int NoteModel::rowCount(const QModelIndex &parent) const
{
    return m_notes.size();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const
{
    QVariant role_data{};

    if (index.row() >= 0 && index.row() < m_notes.size())
    {
        Note note{m_notes.at(index.row())};

        switch (role)
        {
        case Role::Id: role_data = note.id(); break;
        case Role::Heading: role_data = note.heading(); break;
        case Role::State: role_data = note.state(); break;
        case Role::Creation: role_data = note.creation(); break;
        case Role::LastUpdate: role_data = note.lastUpdate(); break;
        case Role::Blocks: role_data = note.blocks(); break;
        }
    }

    return role_data;
}

QHash<int, QByteArray> NoteModel::roleNames() const
{
    QHash<int, QByteArray> roles{};
    roles[Id] = "id";
    roles[Heading] = "heading";
    roles[State] = "state";
    roles[Creation] = "creation";
    roles[LastUpdate] = "lastUpdate";
    roles[Blocks] = "blocks";
    return roles;
}

void NoteModel::addNote(const Note &note)
{
    m_notes.push_back(note);
}
