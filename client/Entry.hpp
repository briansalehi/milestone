#pragma once

#include <QObject>

class Entry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString headline READ headline WRITE headline NOTIFY headlineChanged);
    Q_PROPERTY(QString designator READ designator WRITE designator NOTIFY designatorChanged);

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

signals:
    void headlineChanged();
    void designatorChanged();

private:
    QString m_headline;
    QString m_designator;
};
