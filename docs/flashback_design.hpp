/// \page flashback_design Flashback Design
/// \tableofcontents
///
/// Flashback is one of the major parts of the Milestone project.
///
/// This program consists of simple parts, designed to represent practical
/// contents to users.
///
/// \section flashback_design_principle Flashback Design Principle
///
/// The contents written on flashcards should follow a strict guideline:
///
/// 1.
///
/// \section design_diagram Diagrams
///
/// \startuml
///
/// abstract content
/// {
///     # {abstract} std::ostream operator<<(std::ostream&, content*)
/// }
///
/// class text
/// {
///     - buffer: string
/// }
///
/// content <|-- text
///
/// class list
/// {
///     - elements: string[]
/// }
///
/// content <|-- list
///
/// class inline_code
/// {
///     - buffer: string
/// }
///
/// content <|-- inline_code
///
/// class code_block
/// {
///     - syntax: enum{c,cpp,py,sh,...}
/// }
///
/// content <|-- code_block
///
/// class practice
/// {
///     - question: content*
///     - answer: content*
///     - origins: content*
///     - references: content*
/// }
///
/// practice <-- content
///
/// class topic
/// {
///     - practices: practice[]
/// }
///
/// topic <-- practice
///
/// class subject
/// {
///     - topics: topic[]
/// }
///
/// subject <-- topic
///
/// \enduml
