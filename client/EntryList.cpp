#include <EntryList.hpp>

EntryList::EntryList(QObject *parent)
    : QAbstractListModel{parent}
{
}

int EntryList::rowCount(QModelIndex const& parent) const
{
    return m_entries.size();
}

QVariant EntryList::data(QModelIndex const& index, int role = Qt::DisplayRole) const
{
    QVariant result{};

    if (index.row() >= 0 && index.row() < m_entries.size())
    {
        Entry const& entry { m_entries.at(index.row())};

        if (role == HeadlineRole)
        {
            result = entry.headline();
        }
        else if (role == LastUpdateRole)
        {
            result = entry.lastUpdate();
        }
    }

    return QVariant{};
}

QHash<int, QByteArray> EntryList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[HeadlineRole] = "headline";
    roles[LastUpdateRole] = "lastUpdate";
    return roles;
}

void EntryList::addEntry(Entry const& entry) &
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex{}), rowCount(QModelIndex{}));
    m_entries.push_back(entry);
    endInsertRows();
}

void EntryList::addEntry(Entry&& entry) & noexcept
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex{}), rowCount(QModelIndex{}));
    m_entries.push_back(std::move(entry));
    endInsertRows();
}
