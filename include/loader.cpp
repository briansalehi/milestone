///
/// \page loaders Loaders
/// \brief Database Connections and Loading Components
///
/// Loaders are objecs making connections to databases and fetching required data,
/// or opening files and reading them line by line to aquire data.
///
/// @startuml
/// abstract class Loader {
///     # open(): bool
///     # do_whatever_the_fuck_needed_to_make_product(): std::vector<Product>
///     # close(): void
/// }
///
/// class ResourceLoader {
///     + open(): bool
///     + close(): void
///     + fetch_resources(): std::vector<Resource>
/// }
/// @enduml
///
