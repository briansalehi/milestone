#include <Entry.hpp>
#include <QQmlEngine>

Entry::Entry(QObject *parent)
    : QObject{parent}
    , m_headline{}
    , m_lastUpdate{}
{
}

Entry::Entry(Entry const& copy)
    : QObject{nullptr}
    , m_headline{copy.m_headline}
    , m_lastUpdate{copy.m_lastUpdate}
{
}

Entry& Entry::operator=(Entry const& copy)
{
    m_headline = copy.m_headline;
    m_lastUpdate = copy.m_lastUpdate;
    return *this;
}

Entry::Entry(Entry &&other) noexcept
    : QObject{nullptr}
    , m_headline{std::move(other.m_headline)}
    , m_lastUpdate{std::move(other.m_lastUpdate)}
{
    other.m_headline.clear();
    other.m_lastUpdate.clear();
}

Entry& Entry::operator=(Entry&& other) noexcept
{
    m_headline = std::move(other.m_headline);
    m_lastUpdate = std::move(other.m_lastUpdate);
    other.m_headline.clear();
    other.m_lastUpdate.clear();
    return *this;
}

void Entry::headline(QString const& content)
{
    m_headline = content;
    emit headlineChanged();
}

QString Entry::headline() const
{
    return m_headline;
}

void Entry::lastUpdate(QString const& content)
{
    m_lastUpdate = content;
}

QString Entry::lastUpdate() const
{
    return m_lastUpdate;
}
