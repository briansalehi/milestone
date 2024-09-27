#include "PracticeModel.hpp"
#include <QByteArray>
#include <QHash>

PracticeModel::PracticeModel(QObject *parent)
    : QAbstractListModel{parent}
{}

PracticeModel::PracticeModel(const PracticeModel &other)
    : m_practices(other.m_practices)
{
}

PracticeModel &PracticeModel::operator=(const PracticeModel &other)
{
    m_practices = other.m_practices;
    return *this;
}

PracticeModel::PracticeModel(PracticeModel &&other) noexcept
    : m_practices{std::move(other.m_practices)}
{
}

PracticeModel& PracticeModel::operator=(PracticeModel&& other) noexcept
{
    m_practices = std::move(other.m_practices);
    return *this;
}

int PracticeModel::rowCount(const QModelIndex &parent) const
{
    return m_practices.size();
}

QVariant PracticeModel::data(const QModelIndex &index, int role) const
{
    QVariant role_data{};

    if (index.row() >= 0 && index.row() < m_practices.size())
    {
        Practice note{m_practices.at(index.row())};

        switch (role)
        {
        case Role::Id: role_data = note.id(); break;
        case Role::Heading: role_data = note.heading(); break;
        case Role::Position: role_data = note.position(); break;
        case Role::Creation: role_data = note.creation(); break;
        case Role::LastUpdate: role_data = note.lastUpdate(); break;
        case Role::Blocks: role_data = note.blocks(); break;
        }
    }

    return role_data;
}

QHash<int, QByteArray> PracticeModel::roleNames() const
{
    QHash<int, QByteArray> roles{};
    roles[Id] = "id";
    roles[Heading] = "heading";
    roles[Position] = "position";
    roles[Creation] = "creation";
    roles[LastUpdate] = "lastUpdate";
    roles[Blocks] = "blocks";
    return roles;
}

void PracticeModel::addPractice(const Practice &note)
{
    m_practices.push_back(note);
}
