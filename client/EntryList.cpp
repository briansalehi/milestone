#include <EntryList.hpp>

EntryList::EntryList(QObject *parent)
    : QAbstractListModel{parent}
{
}

EntryList::EntryList(const EntryList &other)
    :  m_entries{other.m_entries}
{
}

EntryList& EntryList::operator=(EntryList const& other)
{
    m_entries = other.m_entries;
    return *this;
}

EntryList::EntryList(EntryList &&other)
    : m_entries{std::move(other.m_entries)}
{
}

EntryList& EntryList::operator=(EntryList&& other)
{
    m_entries = std::move(other.m_entries);
    return *this;
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

        switch (role)
        {
        case HeadlineRole: result = entry.headline(); break;
        case IncompleteSections: result = entry.incompleteSections(); break;
        }
    }

    return result;
}

QHash<int, QByteArray> EntryList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[HeadlineRole] = "headline";
    roles[IncompleteSections] = "incompleteSections";
    return roles;
}

void EntryList::addEntry(Entry const& entry) &
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex{}), rowCount(QModelIndex{}));
    m_entries.push_back(entry);
    endInsertRows();
}
