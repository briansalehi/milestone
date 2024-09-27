#pragma once

#include <Practice.hpp>
#include <QAbstractListModel>
#include <QObject>

class PracticeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role
    {
        Id = Qt::UserRole + 1,
        Heading,
        Position,
        Creation,
        LastUpdate,
        Blocks,
    };

    explicit PracticeModel(QObject *parent = nullptr);

    PracticeModel(PracticeModel const& other);
    PracticeModel& operator=(PracticeModel const& other);

    PracticeModel(PracticeModel&& other) noexcept;
    PracticeModel& operator=(PracticeModel&& other) noexcept;

    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addPractice(Practice const& note);

private:
    std::vector<Practice> m_practices;
};
