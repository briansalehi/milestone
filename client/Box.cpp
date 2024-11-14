#include "Box.hpp"

#include <utility>

Box::Box(QObject *parent): QObject{parent}
{
}

Box::Box(const Box &other)
    : QObject{nullptr}
    , m_id{other.m_id}
    , m_position{other.m_position}
    , m_content{other.m_content}
    , m_type{other.m_type}
    , m_language{other.m_language}
    , m_last_update{other.m_last_update}
{
}

Box& Box::operator=(Box const& other)
{
    m_id = other.m_id;
    m_position = other.m_position;
    m_content = other.m_content;
    m_type = other.m_type;
    m_language = other.m_language;
    m_last_update = other.m_last_update;
    return *this;
}

Box::Box(Box &&other) noexcept
    : QObject{nullptr}
    , m_id{std::move(other.m_id)}
    , m_position{std::move(other.m_position)}
    , m_content{std::move(other.m_content)}
    , m_type{std::move(other.m_type)}
    , m_language{std::move(other.m_language)}
    , m_last_update{std::move(other.m_last_update)}
{
}

Box& Box::operator=(Box&& other) noexcept
{
    m_id = std::move(other.m_id);
    m_position = std::move(other.m_position);
    m_content = std::move(other.m_content);
    m_type = std::move(other.m_type);
    m_language = std::move(other.m_language);
    m_last_update = std::move(other.m_last_update);
    return *this;
}

void Box::id(quint64 arg)
{
    m_id = arg;
}

quint64 Box::id() const
{
    return m_id;
}


void Box::position(quint64 arg)
{
    m_position = arg;
}

quint64 Box::position() const
{
    return m_position;
}


void Box::content(QString arg)
{
    m_content = arg;
}

QString Box::content() const
{
    return m_content;
}


void Box::type(QString arg)
{
    m_type = arg;
}

QString Box::type() const
{
    return m_type;
}


void Box::language(QString arg)
{
    m_language = arg;
}

QString Box::language() const
{
    return m_language;
}


void Box::last_update(QString arg)
{
    m_last_update = arg;
}

QString Box::last_update() const
{
    return m_last_update;
}
