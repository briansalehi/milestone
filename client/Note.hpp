#pragma once

#include <flashback/note.hpp>
#include <QObject>

class Note : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 id READ id WRITE id NOTIFY idChanged);
    Q_PROPERTY(QString heading READ heading WRITE heading NOTIFY headingChanged);
    Q_PROPERTY(QString state READ state WRITE state NOTIFY stateChanged);
    Q_PROPERTY(QString creation READ creation WRITE creation NOTIFY creationChanged);
    Q_PROPERTY(QString lastUpdate READ lastUpdate WRITE lastUpdate NOTIFY lastUpdateChanged);
    Q_PROPERTY(QString blocks READ blocks WRITE blocks NOTIFY blocksChanged);

public:
    explicit Note(QObject *parent = nullptr);
    explicit Note(flashback::note const& note);
    explicit Note(flashback::note&& note);

    Note(Note const& other);
    Note& operator=(Note const& other);

    Note(Note&& other) noexcept;
    Note& operator=(Note&& other) noexcept;

    quint64 id() const;
    void id(quint64 const& id);

    QString heading() const;
    void heading(QString const& heading);

    QString state() const;
    void state(QString const& state);

    QString creation() const;
    void creation(QString const& creation);

    QString lastUpdate() const;
    void lastUpdate(QString const& lastUpdate);

    QString blocks() const;
    void blocks(QString const& blocks);

signals:
    void idChanged();
    void headingChanged();
    void stateChanged();
    void creationChanged();
    void lastUpdateChanged();
    void blocksChanged();

private:
    flashback::note m_note;
};
