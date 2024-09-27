#pragma once

#include <flashback/practice.hpp>
#include <QObject>

class Practice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 id READ id WRITE id NOTIFY idChanged);
    Q_PROPERTY(QString heading READ heading WRITE heading NOTIFY headingChanged);
    Q_PROPERTY(quint32 position READ position WRITE position NOTIFY positionChanged);
    Q_PROPERTY(QString creation READ creation WRITE creation NOTIFY creationChanged);
    Q_PROPERTY(QString lastUpdate READ lastUpdate WRITE lastUpdate NOTIFY lastUpdateChanged);
    Q_PROPERTY(QString blocks READ blocks WRITE blocks NOTIFY blocksChanged);

public:
    explicit Practice(QObject *parent = nullptr);
    explicit Practice(flashback::practice const& practice);
    explicit Practice(flashback::practice&& practice);

    Practice(Practice const& other);
    Practice& operator=(Practice const& other);

    Practice(Practice&& other) noexcept;
    Practice& operator=(Practice&& other) noexcept;

    quint64 id() const;
    void id(quint64 const& id);

    QString heading() const;
    void heading(QString const& heading);

    quint32 position() const;
    void position(quint32 const position);

    QString creation() const;
    void creation(QString const& creation);

    QString lastUpdate() const;
    void lastUpdate(QString const& lastUpdate);

    QString blocks() const;
    void blocks(QString const& blocks);


signals:
    void idChanged();
    void headingChanged();
    void positionChanged();
    void creationChanged();
    void lastUpdateChanged();
    void blocksChanged();

private:
    flashback::practice m_practice;
};
