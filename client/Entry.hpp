#pragma once

#include <QObject>

class Entry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString headline READ headline WRITE headline NOTIFY headlineChanged);
    Q_PROPERTY(QString incompleteSections READ incompleteSections WRITE incompleteSections NOTIFY incompleteSectionsChanged);

public:
    explicit Entry(QObject *parent = nullptr);

    Entry(Entry const& copy);
    Entry& operator=(Entry const& copy);

    Entry(Entry&& other) noexcept;
    Entry& operator=(Entry&& other) noexcept;

    void headline(QString const& content);
    QString headline() const;

    void incompleteSections(QString sections);
    QString incompleteSections() const;

signals:
    void headlineChanged();
    void incompleteSectionsChanged();

private:
    QString m_headline;
    QString m_incompleteSections;
};
