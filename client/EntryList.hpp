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
        HeadlineRole = Qt::UserRole + 1,
        LastUpdateRole
    };

    explicit EntryList(QObject *parent = nullptr);

    int rowCount(QModelIndex const& parent) const override;

    QVariant data(QModelIndex const& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addEntry(Entry const& entry) &;
    void addEntry(Entry&& entry) & noexcept;

private:
    std::vector<Entry> m_entries;
};
