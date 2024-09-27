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
#include <PracticeModel.hpp>
#include <flashback/flashback.hpp>
#include <flashback/subject.hpp>
#include <flashback/topic.hpp>
#include <flashback/practice.hpp>
#include <flashback/resource.hpp>
#include <flashback/section.hpp>
#include <flashback/note.hpp>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);

    Q_INVOKABLE EntryList* subjects();
    Q_INVOKABLE EntryList* topics(std::uint64_t const subject_id);
    Q_INVOKABLE PracticeModel* practices(std::uint64_t const topic_id);
    Q_INVOKABLE EntryList* resources();
    Q_INVOKABLE EntryList* sections(std::uint64_t const resource_id);
    Q_INVOKABLE NoteModel* notes(std::uint64_t const section_id);

signals:

private:
    flashback::database m_database;
};
