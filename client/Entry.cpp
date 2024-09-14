#include <Entry.hpp>
#include <QQmlEngine>

Entry::Entry(QObject *parent)
    : QObject{parent}
{
}

Entry::Entry(Entry const& copy)
    : QObject{nullptr}
    , m_headline{copy.m_headline}
    , m_incompleteSections{copy.m_incompleteSections}
{
}

Entry& Entry::operator=(Entry const& copy)
{
    m_headline = copy.m_headline;
    m_incompleteSections = copy.m_incompleteSections;
    return *this;
}

Entry::Entry(Entry &&other) noexcept
    : QObject{nullptr}
    , m_headline{std::move(other.m_headline)}
    , m_incompleteSections{std::move(other.m_incompleteSections)}
{
    other.m_headline.clear();
    other.m_incompleteSections.clear();
}

Entry& Entry::operator=(Entry&& other) noexcept
{
    m_headline = std::move(other.m_headline);
    m_incompleteSections = std::move(other.m_incompleteSections);
    other.m_headline.clear();
    other.m_incompleteSections.clear();
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

void Entry::incompleteSections(QString sections)
{
    m_incompleteSections = sections;
}

QString Entry::incompleteSections() const
{
    return m_incompleteSections;
}
