#pragma once

#include <QAbstractListModel>
#include <QModelIndex>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <QHash>
#include <Entry.hpp>
#include <vector>

class EntryList : public QAbstractListModel
{
    Q_OBJECT

public:
    enum EntryRole
    {
        Headline = Qt::UserRole + 1,
        Designator,
        Id
    };

    explicit EntryList(QObject *parent = nullptr);
    EntryList(EntryList const& other);
    EntryList& operator=(EntryList const& other);
    EntryList(EntryList&& other);
    EntryList& operator=(EntryList&& other);

    int rowCount(QModelIndex const& parent) const override;

    QVariant data(QModelIndex const& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addEntry(Entry const& entry) &;

    void clear() noexcept;

private:
    std::vector<Entry> m_entries;
};
