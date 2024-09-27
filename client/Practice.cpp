#include "Practice.hpp"

Practice::Practice(QObject *parent)
    : QObject{parent}
{}

Practice::Practice(const flashback::practice &practice)
{
    m_practice = practice;
}

Practice::Practice(flashback::practice &&practice)
{
    m_practice = std::move(practice);
}

Practice::Practice(const Practice &other)
    : m_practice{other.m_practice}
{
}

Practice &Practice::operator=(const Practice &other)
{
    m_practice = other.m_practice;
    return *this;
}

Practice::Practice(Practice &&other) noexcept
    : m_practice{std::move(other.m_practice)}
{
}

Practice& Practice::operator=(Practice&& other) noexcept
{
    m_practice = std::move(other.m_practice);
    return *this;
}


quint64 Practice::id() const
{
    return m_practice.id;
}

void Practice::id(const quint64 &id)
{
    m_practice.id = id;
}

QString Practice::heading() const
{
    return QString::fromStdString(m_practice.heading);
}

void Practice::heading(const QString &heading)
{
    m_practice.heading = heading.toStdString();
}

quint32 Practice::position() const
{
    return m_practice.position;
}

void Practice::position(quint32 const position)
{
    m_practice.position = position;
}

QString Practice::creation() const
{
    std::string formated_date{std::format("{}", m_practice.creation)};
    return QString::fromStdString(formated_date);
}

void Practice::creation(const QString &creation)
{
}

QString Practice::lastUpdate() const
{
    std::string formated_date{std::format("{}", m_practice.last_update)};
    return QString::fromStdString(formated_date);
}

void Practice::lastUpdate(const QString &lastUpdate)
{
}

QString Practice::blocks() const
{
    std::stringstream buffer;
    for (flashback::block const& block: m_practice.blocks)
    {
        buffer << block.content << "\n\n";
    }

    return QString::fromStdString(buffer.str());
}

void Practice::blocks(const QString &blocks)
{
}
