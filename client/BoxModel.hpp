#pragma once

#include <Box.hpp>
#include <QAbstractListModel>
#include <QObject>

class BoxModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role
    {
        Id = Qt::UserRole + 1,
        Position,
        Content,
        Type,
        Language,
        LastUpdate
    };

    explicit BoxModel(QObject *parent = nullptr);

    BoxModel(BoxModel const& other);
    BoxModel& operator=(BoxModel const& other);

    BoxModel(BoxModel&& other) noexcept;
    BoxModel& operator=(BoxModel&& other) noexcept;

    int rowCount(QModelIndex const& parent) const override;

    QVariant data(QModelIndex const& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addBox(Box const& box);

private:
    std::vector<Box> m_boxes;
};
