///
/// \page definitions_page Definitions
/// \brief Definitions Used in Program Design
/// \tableofcontents
///
/// There are several definitions you will encounter while reading the design
/// decisions of this program.\n
/// Of many definitions, a few are not used in a programatic sense. Hence,
/// they will not appear in the code, but they will be used to point to abstract
/// definitions or real entities but unrelated to the design of program itself.\n
/// The rest of definitions will be directly used to point out different aspects
/// of the program.
///
/// \section program_lifetime Program Lifetime
///
/// There are two definitions in the program lifetime:
///
/// - \ref session_definition
/// - \ref progress_definition
///
/// These definitions are only related to the program itself.
///
/// \subsubsection session_definition Session
///
/// A session is the time duration in which user actively interacts with practices.\n
/// This time span is not necessarily as long as the whole life time of the program itself.
///
/// @startuml
/// !theme cyborg
/// concise "Program" as p
/// concise "User" as u
/// robust "Session" as s
///
/// @p
/// 0 is Waiting
/// 5 is Running
/// 30 is Waiting
/// 
/// @u
/// 0 is Idle
/// 5 is Practicing
/// 30 is Idle

/// @s
/// 0 is Inactive
/// 5 is Active
/// 30 is Inactive
/// 35 is Inactive
/// @enduml
///
/// \subsubsection progress_definition Progress
/// 
/// Progress is all the information gathered from user activity during sessions
/// stored in a non-volatile memory.\n
/// Progress can be restored and used later after a new session starts.
///
/// @startuml
/// start
/// :Restore previous progress;
/// :User interacts;
/// :Save progress;
/// end
/// @enduml
///
/// Each time the progress is saved, the session information should be recorded
/// on non-volatile memory.\n
/// The information required from each session is:
///
/// - How long did the session took to finish?
/// - How many notes or practices has user done?
/// - What was the last note or practice that user see?
///
/// \section program_structure Program Structure
///
/// The program consists of two components:
///
/// - \ref registry_definition
/// - \ref recollection_definition
///
/// Each of these components can be used based on user decision.\n
/// The definition of these components are as follows:
///
/// \section registry_definition Registry Component
///
/// Registry is a place where user can find resources, and to step through the notes
/// taken from those resources, in order to review the subject represented by
/// that resource.\n
///
/// @startuml
/// !theme cyborg
/// left to right direction
/// :Client: as c
/// (Registry Component) as g
/// (Recollection Component) as r
/// note "Review previous chapters\nof a book" as n
/// c --> g
/// c --> r
/// g .. n
/// @enduml
///
/// For example, a user might want to find the book *Introduction to Linear Algebra*
/// authored by *Nathaniel Johnston*, and then review notes of the first 5 chapters
/// in order to step forward and read the 6th chapter.
///
/// The \ref registry_interface consists of two objects:
///
/// - \ref resource_definition
/// - \ref note_definition
///
/// \subsubsection resource_definition Resource
///
/// Resource is an object that contains technical information outside the scope of
/// the program, and is usually what practices are refering to.
/// A resource can be a book, website, video, course or any technically valuable piece
/// of data worth learning.
///
/// Each resource contains many \ref note_definition.
///
/// @startuml
/// !theme cyborg
/// left to right direction
///
/// map Resource {
///     title => Linear Algebra
/// }
///
/// map Note1 {
///     text => data
///     position => chapter 1
/// }
///
/// map Note2 {
///     text => data
///     position => chapter 1
/// }
///
/// map Note3 {
///     text => data
///     position => chapter 2
/// }
///
/// Resource *-- Note1
/// Resource *-- Note2
/// Resource *-- Note3
/// @enduml
///
/// \subsubsection note_definition Note
///
/// Notes are text samples taken from resources, and they are strongly
/// resource dependent.\n
/// Meaning that notes are predicative texts directly picked from resources, and
/// only have educational values, but later will be used to create
/// \ref practice_definition objects in a question and answer form.
///
/// \section recollection_definition Recollection Component
///
/// On the other hand, the \ref recollection_definition is where user can practice
/// by being asked questions about the topics of a specific subject, and compare their
/// answers.\n
/// This is regardless of what resources are available to this subject.
///
/// @startuml
/// !theme cyborg
/// left to right direction
/// :Client: as c
/// (Registry Component) as g
/// (Recollection Component) as r
/// note "Practice all the topics\nof a subject at least once" as n
/// c --> g
/// c --> r
/// r .. n
/// @enduml
///
/// For example, a user has already read the book *Introduction to Linear Algebra*,
/// and wants to practice the subject **Linear Algebra**, disregarding available
/// books covering this subject.\n
/// Here, user enters the \ref recollection_definition, the program lists a series
/// of questions, minimally picked to be practiced on the shortest time duration
/// possible, short enough to give user at least one question for each topic in the
/// subject.
///
/// The \ref recollection_interface consists of following objects:
///
/// - \ref subject_definition
/// - \ref topic_definition
/// - \ref practice_definition
/// - \ref reference_definition
///
/// \subsubsection subject_definition Subject
///
/// Any practice and resource used in this program is related to a subject matter,
/// discussing a specific material.\n
///
/// @startuml
/// !theme cyborg
/// left to right direction
/// map Subject1 {
///     title => Calculus
/// }
/// map Subject2 {
///     title => Linear Algebra
/// }
/// map Subject3 {
///     title => Statistics
/// }
/// Subject1 <--> Subject2
/// Subject2 <--> Subject3
/// @enduml
///
/// \subsubsection topic_definition Topic
///
/// Each \ref subject_definition consists of related but distinguishable sections,
/// all together forming that material.\n
/// Every distinguishable section of a \ref subject_definition will be referred to as
/// a topic.
///
/// Each \ref subject_definition consists of many topics.
///
/// @startuml
/// !theme cyborg
///
/// map Subject {
///     title => Python Programming
/// }
///
/// map Topics {
///     1 => Classes
///     2 => Network
///     3 => JSON
/// }
///
/// Subject   "1" *-- "many" Topics
/// @enduml
///
/// For example, **Python programming language** is a subject,
/// while **network programming** is one of the topics covered in this subject.
///
/// \subsubsection practice_definition Practice
///
/// Practice is an entity which holds \ref resource_definition information in runtime.\n
/// This information can be used to represent user the technical information needed for
/// recollection.
///
/// Each \ref topic_definition contains many practices.
///
/// @startuml
/// !theme cyborg
/// left to right direction
///
/// map Subject {
///     title => Linear Algebra
/// }
///
/// map Topic1 {
///     title => Vectors
/// }
///
/// map Topic2 {
///     title => Vector to Scalar Multiplication
/// }
///
/// map Topic3 {
///     title => Dot Product
/// }
///
/// map Practices1 {
///     1 => Question
///     2 => Question
///     3 => Question
/// }
///
/// map Practices2 {
///     1 => Question
///     2 => Question
///     3 => Question
/// }
///
/// map Practices3 {
///     1 => Question
///     2 => Question
///     3 => Question
/// }
///
/// Subject *-- Topic1
/// Subject *-- Topic2
/// Subject *-- Topic3
/// Topic1 *-- Practices1
/// Topic2 *-- Practices2
/// Topic3 *-- Practices3
/// @enduml
///
/// For example, **Linear Algebra** is a subject, while **Matrix Multiplication**
/// is a topic to be discussed, and this topic may contain many practices in this
/// program.
///
/// \subsubsection reference_definition Reference
///
/// Reference is a link from practice objects into resources.
///
/// @startuml
/// !theme cyborg
/// left to right direction
///
/// map Subject {
///     title => Linear Algebra
/// }
///
/// map Topic1 {
/// }
///
/// map Topic2 {
///     title => Vector to Scalar Multiplication
/// }
///
/// map Topic3 {
/// }
///
/// map Practice1 {
///     Question => Answer
/// }
///
/// map Practice2 {
///     Question => Answer
/// }
///
/// map Practice3 {
///     Question => Answer
/// }
///
/// map Reference1 {
///     target => Resource
///     position => Chapter 2
/// }
///
/// map Reference2 {
///     target => Resource
///     position => Chapter 2
/// }
///
/// map Reference3 {
///     target => Resource
///     position => Chapter 2
/// }
///
/// Subject *-- Topic1
/// Subject *-- Topic2
/// Subject *-- Topic3
/// Topic2 *-- Practice1
/// Topic2 *-- Practice2
/// Topic2 *-- Practice3
/// Practice1 *-- Reference1
/// Practice2 *-- Reference2
/// Practice3 *-- Reference3
/// @enduml
///
/// References can either be a website, book, course, or an article.\n
/// In either case, they should have a generic way of representing what is the
/// position of that resource which the practice was aimed to be written.
///

