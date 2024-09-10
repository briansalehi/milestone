#include <EntryList.hpp>

EntryList::EntryList(QObject *parent)
    : QAbstractListModel{parent}
    , m_entries()
{
}

int EntryList::rowCount(QModelIndex const&) const
{
    return m_entries.size();
}

QVariant EntryList::data(QModelIndex const& index, int role = Qt::DisplayRole) const
{
    if (index.row() < 0 || index.row() >= m_entries.size())
        return QVariant{};

    Entry const& entry = m_entries.at(index.row());

    if (role == HeadlineRole)
        return entry.headline();
    else if (role == LastUpdateRole)
        return entry.lastUpdate();

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
