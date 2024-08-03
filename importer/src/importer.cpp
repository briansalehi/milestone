#include <flashback/importer.hpp>

namespace flashback
{
explicit importer::importer(int argc, char** argv)
{
}

std::vector<record> importer::records() const
{
    return m_records;
}

void importer::store(record const& )
{
    pqxx::connection connection{"postgres://localhost/flashback"};
    pqxx::work task{connection};
    pqxx::result result = task.exec("select now()");
}
} // flashback
