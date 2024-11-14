#include "BoxModel.hpp"

#include <QVariant>

BoxModel::BoxModel(QObject *parent): QAbstractListModel{parent}
{}

BoxModel::BoxModel(const BoxModel &other): m_boxes{std::move(other.m_boxes)}
{
}

BoxModel& BoxModel::operator=(BoxModel const& other)
{
    m_boxes = other.m_boxes;
    return *this;
}

BoxModel::BoxModel(BoxModel &&other) noexcept: m_boxes{std::move(other.m_boxes)}
{
}

BoxModel& BoxModel::operator=(BoxModel&& other) noexcept
{
    m_boxes = std::move(other.m_boxes);
    return *this;
}

int BoxModel::rowCount(const QModelIndex &parent) const
{
    return m_boxes.size();
}

QVariant BoxModel::data(const QModelIndex &index, int role) const
{
    QVariant role_data{};

    if (index.row() >= 0 && index.row() < m_boxes.size())
    {
        Box box{m_boxes.at(index.row())};

        switch (role)
        {
        case Role::Id: role_data = box.id(); break;
        case Role::Position: role_data = box.position(); break;
        case Role::Content: role_data = box.content(); break;
        case Role::Type: role_data = box.type(); break;
        case Role::Language: role_data = box.language(); break;
        case Role::LastUpdate: role_data = box.last_update(); break;
        }
    }

    return role_data;
}

QHash<int, QByteArray> BoxModel::roleNames() const
{
    QHash<int, QByteArray> roles{};
    roles[Id] = "id";
    roles[Position] = "position";
    roles[Content] = "content";
    roles[Type] = "type";
    roles[Language] = "language";
    roles[LastUpdate] = "last_update";
    return roles;
}

void BoxModel::addBox(const Box &box)
{
    m_boxes.push_back(box);
}
