#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkRequestFactory>
#include <QNetworkAddressEntry>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkInformation>
#include <QNetworkInterface>
#include <QNetworkCookieJar>
#include <QtNetworkAuth/QtNetworkAuth>
#include <QtNetworkAuth/QtNetworkAuthDepends>
#include <QtNetworkAuth/QtNetworkAuthVersion>
#include <QtNetworkAuth/QAbstractOAuth2>
#include <QtNetworkAuth/QAbstractOAuthReplyHandler>

#include <EntryList.hpp>
#include <Entry.hpp>
#include <flashback/flashback.hpp>

class Database : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Database(QObject *parent = nullptr);

    EntryList entryList() const;

signals:

private:
    flashback::database m_database;
    EntryList m_entryList;
};
