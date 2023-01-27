#pragma once

///
/// \page loaders Loaders
/// \brief Database Connections and Loading Components
///
/// Loaders are objecs making connections to databases and fetching required data,
/// or opening files and reading them line by line to aquire data.
///
/// @startuml
/// abstract class Loader {
///     # fetch_content(): void
/// }
///
/// class ResourceLoader {
///     # fetch_content(): void
///     - add_resource(): void
///     + resources(): std::vector<Resource>
///     + entities_path(): std::filesyste::path
/// }
///
/// class SubjectLoader {
///     # fetch_content(): void
///     - add_subject(): void
///     + subjects(): std::vector<Subject>
///     + database_address(): std::string
/// }
///
/// Loader <-- ResourceLoader
/// Loader <-- SubjectLoader
/// @enduml
///

namespace flashback
{
class loader
{
public:
    virtual ~loader() {}

    virtual void fetch_content() = 0;
    virtual bool connected() const = 0;
};

} // flashback
