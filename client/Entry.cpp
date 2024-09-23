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
    , m_id{copy.m_id}
{
}

Entry& Entry::operator=(Entry const& copy)
{
    m_headline = copy.m_headline;
    m_designator = copy.m_designator;
    m_id = copy.m_id;
    return *this;
}

Entry::Entry(Entry &&other) noexcept
    : QObject{nullptr}
    , m_headline{std::move(other.m_headline)}
    , m_designator{std::move(other.m_designator)}
    , m_id{std::move(other.m_id)}
{
    other.m_headline.clear();
    other.m_designator.clear();
    other.m_id = 0;
}

Entry& Entry::operator=(Entry&& other) noexcept
{
    m_headline = std::move(other.m_headline);
    m_designator = std::move(other.m_designator);
    m_id = std::move(other.m_id);
    other.m_headline.clear();
    other.m_designator.clear();
    other.m_id = 0;
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
    emit designatorChanged();
}

QString Entry::designator() const
{
    return m_designator;
}

void Entry::id(const int value)
{
    m_id = value;
    emit idChanged();
}

int Entry::id() const
{
    return m_id;
}
