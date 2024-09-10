#pragma once

#include <QObject>

class Entry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString headline READ headline WRITE headline NOTIFY headlineChanged);
    Q_PROPERTY(QString lastUpdate READ lastUpdate WRITE lastUpdate NOTIFY lastUpdateChanged);

public:
    explicit Entry(QObject *parent = nullptr);

    Entry(Entry const& copy);
    Entry& operator=(Entry const& copy);

    Entry(Entry&& other) noexcept;
    Entry& operator=(Entry&& other) noexcept;

    void headline(QString const& content);
    QString headline() const;

    void lastUpdate(QString const& content);
    QString lastUpdate() const;

signals:
    void headlineChanged();
    void lastUpdateChanged();

private:
    QString m_headline;
    QString m_lastUpdate;
};
