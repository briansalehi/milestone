#include <Entry.hpp>
#include <QQmlEngine>

Entry::Entry(QObject *parent)
    : QObject{parent}
{
}

Entry::Entry(Entry const& copy)
    : QObject{nullptr}
    , m_headline{copy.m_headline}
    , m_designator{copy.m_designator}
{
}

Entry& Entry::operator=(Entry const& copy)
{
    m_headline = copy.m_headline;
    m_designator = copy.m_designator;
    return *this;
}

Entry::Entry(Entry &&other) noexcept
    : QObject{nullptr}
    , m_headline{std::move(other.m_headline)}
    , m_designator{std::move(other.m_designator)}
{
    other.m_headline.clear();
    other.m_designator.clear();
}

Entry& Entry::operator=(Entry&& other) noexcept
{
    m_headline = std::move(other.m_headline);
    m_designator = std::move(other.m_designator);
    other.m_headline.clear();
    other.m_designator.clear();
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

void Entry::designator(QString sections)
{
    m_designator = sections;
}

QString Entry::designator() const
{
    return m_designator;
}
