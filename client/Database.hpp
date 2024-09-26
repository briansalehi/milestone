#pragma once

#include <QObject>
//#include <QNetworkReply>
//#include <QNetworkRequest>
//#include <QNetworkRequestFactory>
//#include <QNetworkAddressEntry>
//#include <QNetworkAccessManager>
//#include <QNetworkCookie>
//#include <QNetworkInformation>
//#include <QNetworkInterface>
//#include <QNetworkCookieJar>
//#include <QtNetworkAuth/QtNetworkAuth>
//#include <QtNetworkAuth/QtNetworkAuthDepends>
//#include <QtNetworkAuth/QtNetworkAuthVersion>
//#include <QtNetworkAuth/QAbstractOAuth2>
//#include <QtNetworkAuth/QAbstractOAuthReplyHandler>

#include <EntryList.hpp>
#include <NoteModel.hpp>
#include <flashback/flashback.hpp>
#include <flashback/subject.hpp>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);

    Q_INVOKABLE EntryList* subjects();
    Q_INVOKABLE EntryList* studying_resources();
    Q_INVOKABLE EntryList* editing_resources();
    Q_INVOKABLE EntryList* get_studying_sections(std::uint64_t const resource_id);
    Q_INVOKABLE EntryList* editing_sections(std::uint64_t const resource_id);
    Q_INVOKABLE NoteModel* section_studying_notes(std::uint64_t const section_id);

signals:

private:
    flashback::database m_database;
};
