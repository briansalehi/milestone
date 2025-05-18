/**
 * \page design_overview Design Overview
 * \tableofcontents
 *
 * This program consists of several components, all connected to each other in order to make a general workflow.
 *
 * \section structure_overview Structure Overview
 *
 * Following is the overall structure of the components used in milestone project:
 *
 * @startuml
 *
 * interface user_interface {
 * }
 *
 * class gui {
 * }
 *
 * class cli {
 * }
 *
 * user_interface <|-- cli
 * user_interface <|-- gui
 *
 * interface client as "Client" {
 *     - ui: user_interface
 * }
 *
 * user_interface -* client
 *
 * cloud internet as "Internet" {
 *     class server as "Server" {
 *     }
 *
 *     interface database as "Database" {
 *     }
 *
 *     class postgres {
 *     }
 *
 *     database <|- postgres
 * }
 *
 * server <--> client: grpc
 * server <-> database : grpc
 *
 * @enduml
 *
 * \section flashback_design_principle Flashback Design Principle
 *
 * The contents written on flashcards should follow a strict guideline:
 *
 * 1.
 *
 * \section design_diagram Diagrams
 *
 * \startuml
 *
 * abstract content
 * {
 *     # {abstract} std::ostream operator<<(std::ostream&, content*)
 * }
 *
 * class text
 * {
 *     - buffer: string
 * }
 *
 * content <|-- text
 *
 * class list
 * {
 *     - elements: string[]
 * }
 *
 * content <|-- list
 *
 * class inline_code
 * {
 *     - buffer: string
 * }
 *
 * content <|-- inline_code
 *
 * class code_block
 * {
 *     - syntax: enum{c,cpp,py,sh,...}
 * }
 *
 * content <|-- code_block
 *
 * class practice
 * {
 *     - question: content*
 *     - answer: content*
 *     - origins: content*
 *     - references: content*
 * }
 *
 * practice <-- content
 *
 * class topic
 * {
 *     - practices: practice[]
 * }
 *
 * topic <-- practice
 *
 * class subject
 * {
 *     - topics: topic[]
 * }
 *
 * subject <-- topic
 *
 * \enduml
 */