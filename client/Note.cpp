#include "Note.hpp"
#include <iostream>
#include <sstream>
#include <ranges>
#include <algorithm>

Note::Note(QObject *parent)
    : QObject{parent}
{}

Note::Note(const flashback::note &note)
{
    this->note = note;
}

Note::Note(flashback::note &&note)
{
    this->note = std::move(note);
}

Note::Note(const Note &other)
    : note{other.note}
{
}

Note &Note::operator=(const Note &other)
{
    note = other.note;
    return *this;
}

Note::Note(Note &&other) noexcept
    : note{std::move(other.note)}
{
}

Note& Note::operator=(Note&& other) noexcept
{
    note = std::move(other.note);
    return *this;
}


quint64 Note::id() const
{
    return note.id;
}

void Note::id(const quint64 &id)
{
    note.id = id;
}

QString Note::heading() const
{
    return QString::fromStdString(note.heading);
}

void Note::heading(const QString &heading)
{
    note.heading = heading.toStdString();
}

QString Note::state() const
{
    QString current_state{};

    switch (note.state)
    {
    using flashback::publication_state;
    case publication_state::open: current_state = "open"; break;
    case publication_state::writing: current_state = "writing"; break;
    case publication_state::completed: current_state = "completed"; break;
    case publication_state::revised: current_state = "revised"; break;
    case publication_state::approved: current_state = "approved"; break;
    case publication_state::validated: current_state = "validated"; break;
    case publication_state::released: current_state = "released"; break;
    case publication_state::ignored: current_state = "ignored"; break;
    }

    return current_state;
}

void Note::state(const QString &state)
{
    if (state == "open") note.state = flashback::publication_state::open;
    else if (state == "writing") note.state = flashback::publication_state::writing;
    else if (state == "completed") note.state = flashback::publication_state::completed;
    else if (state == "revised") note.state = flashback::publication_state::revised;
    else if (state == "approved") note.state = flashback::publication_state::approved;
    else if (state == "validated") note.state = flashback::publication_state::validated;
    else if (state == "released") note.state = flashback::publication_state::released;
    else if (state == "ignored") note.state = flashback::publication_state::ignored;
}

QString Note::creation() const
{
    std::string formated_date{std::format("{}", note.creation)};
    return QString::fromStdString(formated_date);
}

void Note::creation(const QString &creation)
{
}

QString Note::lastUpdate() const
{
    std::string formated_date{std::format("{}", note.last_update)};
    return QString::fromStdString(formated_date);
}

void Note::lastUpdate(const QString &lastUpdate)
{
}

QString Note::blocks() const
{
    std::stringstream buffer;
    for (flashback::note_block const& block: note.blocks)
    {
        buffer << block.content << "\n\n";
    }

    return QString::fromStdString(buffer.str());
}

void Note::blocks(const QString &blocks)
{
}

