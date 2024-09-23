#pragma once

#include <QObject>

class Entry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString headline READ headline WRITE headline NOTIFY headlineChanged);
    Q_PROPERTY(QString designator READ designator WRITE designator NOTIFY designatorChanged);
    Q_PROPERTY(int id READ id WRITE id NOTIFY idChanged);

public:
    explicit Entry(QObject *parent = nullptr);

    Entry(Entry const& copy);
    Entry& operator=(Entry const& copy);

    Entry(Entry&& other) noexcept;
    Entry& operator=(Entry&& other) noexcept;

    void headline(QString const& content);
    QString headline() const;

    void designator(QString sections);
    QString designator() const;

    void id(int const value);
    int id() const;

signals:
    void headlineChanged();
    void designatorChanged();
    void idChanged();

private:
    QString m_headline;
    QString m_designator;
    int m_id;
};
