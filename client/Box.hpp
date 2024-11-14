#pragma once

#include <QObject>
#include <QString>

class Box : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 id READ id WRITE id NOTIFY idChanged);
    Q_PROPERTY(quint64 position READ position WRITE position NOTIFY positionChanged);
    Q_PROPERTY(QString content READ content WRITE content NOTIFY contentChanged);
    Q_PROPERTY(QString type READ type WRITE type NOTIFY typeChanged);
    Q_PROPERTY(QString language READ language WRITE language NOTIFY languageChanged);
    Q_PROPERTY(QString last_update READ last_update WRITE last_update NOTIFY last_updateChanged);

public:
    explicit Box(QObject *parent = nullptr);
    Box(Box const& other);
    Box(Box&& other) noexcept;
    Box& operator=(Box const& other);
    Box& operator=(Box&& other) noexcept;

    void id(quint64 arg);
    quint64 id() const;

    void position(quint64 arg);
    quint64 position() const;

    void content(QString arg);
    QString content() const;

    void type(QString arg);
    QString type() const;

    void language(QString arg);
    QString language() const;

    void last_update(QString arg);
    QString last_update() const;

signals:
    void idChanged();
    void positionChanged();
    void contentChanged();
    void typeChanged();
    void languageChanged();
    void last_updateChanged();

private:
    quint64 m_id;
    quint64 m_position;
    QString m_content;
    QString m_type;
    QString m_language;
    QString m_last_update;
};
