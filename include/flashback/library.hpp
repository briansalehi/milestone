#pragma once

#include <flashback/reference.hpp>
#include <flashback/resource.hpp>
#include <flashback/console.hpp>
#include <flashback/loader.hpp>
#include <flashback/space.hpp>

#include <filesystem>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <ranges>

namespace flashback
{

///
/// \page library_space Library
///
/// \brief A space where you can review the books and resources you already used.
///
/// This class contains the user specified resources and notes within them.\n
/// These resources can be books, video courses, articles or anything valuable
/// enough to be used as a resource.
///
/// * \ref resource
/// * \ref note
/// * \ref reference
///
/// In library section, User can search through resources and select one.\n
/// Then they will be able to see the notes captured from that resource.
///
/// \section dashboard Dashboard
///
/// To enter the library space, user should first enter into dashboard:
///
/// \startuml
/// !theme cyborg
/// start
/// :Run the program;
/// :Open Dashboard;
/// switch (Select a space)
/// case (Library)
///     #green:Initialize Library Space;
/// case (Trainer)
///     :Initialize Trainer Space;
/// case (Milestone)
///     :Initialize Milestone Space;
/// case (Roadmap)
///     :Initialize Roadmap Space;
/// endswitch
/// end
/// \enduml
///
/// \subsection library_space Library Space
///
/// When user enters into this space, they will be able to do following tasks:
///
/// * Select a resource from list of available resources
/// * Add a resource into the list of resources
/// * Edit a resource in order to update or correct resource information
/// * Remove a resource which is only allowed by admins
///
/// The diagram of user choices is as follows:
///
/// \startuml
/// !theme cyborg
/// start
/// :Initialize Library Space;
/// if (User recently used resources?) then (yes)
///     :List recently used resources;
/// else (no)
///     :List top used resources;
/// endif
///
/// switch (Perform an action on resources)
/// case (Select)
///     :Select a resource;
///     :Load notes\nwithin resource;
///     #green:Show note operations;
/// case (Add)
///     :Prompt for title;
///     :Create resource;
///     :Insert resource\ninto database;
/// case (Edit)
///     :Undefined;
/// case (Remove)
///     :Undefined;
/// endswitch
/// end
/// \enduml
///
/// By selecting a resource, notes belonging to that resource will be listed and
/// user will be able to do specific tasks on those notes:
///
/// \startuml
/// !theme cyborg
/// :Load notes in order;
/// switch (Show note operations)
/// case (Select)
///     :Select note;
///
///     repeat
///     :Show note;
///     backward:Load next note;
///     repeat while (Next note?) is (yes)
/// case (Add)
///     :;
/// case (Edit)
///     :;
/// case (Remove)
///     :;
/// endswitch
/// \enduml
///
/// This space consists of three components:
///
/// - \ref resource
/// - \ref note
/// - \ref position
///
/// In library section, User can search through resources and select one.\n
/// Then they will be able to see the notes captured from that resource.
///
/// Notes can be used to review a resource. Though, user should be aware that
/// following the subject of that resource only by using that resource is not a
/// wise choice, but it's best to use \ref tutorial_space to learn that subject
/// and then use \ref trainer_space space to practice the topics
/// of that subject.
///
/// Resources will be loaded into the program from any available database,
/// either files in the first stage of the program or relational or non-relational
/// databases, through \ref loaders.
///
/// \subsection resource_interface Resource
///
/// \ref book is an abstract class in program which holds information
/// of a specific real \ref book_entity .\n
/// A \ref book also holds series of \ref practice objects which is required for
/// recollection procedure.
///
/// A resource may be a link, a book, a course, or an article.\n
/// So resource must be an interface, so that its derivations extend it.
///
/// The resource interface should at least have following core methods:
///
/// \startuml
/// abstract class Resource {
///     # title(): std::string
///     # notes(): std::set<Note>
/// }
///
/// class Book {
///     # chapters(): unsigned int
/// }
///
/// class Course {
///     # duration(): std::chrono::duration
/// }
///
/// Resource <|-- Book
/// Resource <|-- Course
/// \enduml
///
/// \subsection note_interface Note
///
/// \ref note_definition objects are simple data objects holding text
/// values picked directly from their corresponding \ref resource_definition objects.
///
/// \startuml
/// struct Note {
///     + title: std::string
///     + description: std::string
///     + position: Position
///     + collected: bool
///     # operator<(other: Note const&): bool
///     # operator!=(other: Note const&): bool
/// }
///
/// abstract class Position {
///     # operator<(other: Position const&): bool
///     # operator!=(other: Position const&): bool
/// 
/// }
///
/// Note <|-- Position
/// \enduml
///
/// Notes hold text from resources, either a resource be a video or a book, the final
/// conversion of them will be texual notes.
///
/// Notes have a flag indicating whether it has collected from \ref library_definition
/// to the \ref recollection_definition, because notes are the final product of
/// \ref library_definition, and they will be copied into the \ref recollection_definition
/// and will be modified accordingly so that they turn into question-answer form.
///
/// \subsection position_interface Position
///
/// Positions are resource specific locations where the text was taken from.\n
/// Positions might locate pages and chapters of a book, or a duration of course.
///
/// \startuml
/// abstract class Position {
///     # operator<(other: Position const&): bool
///     # operator!=(other: Position const&): bool
/// }
///
/// class BookPosition {
/// }
///
/// class CoursePosition {
/// }
///
/// Position <|-- BookPosition
/// Position <|-- CoursePosition
/// \enduml
///
class library: public space
{
public:
    enum class library_actions {undefined, list_resources, search_resource};
    enum class resource_actions {undefined, show, add, edit, remove};
    enum class note_actions {undefined, expand, next, previous, collect, add, edit, remove};

    explicit library(std::filesystem::path const&);

public:
    ///
    /// Resources should be loaded in initialization.
    /// They should be sorted either by recent usage of user
    /// or by mostly used resources by users.
    /// \todo User implementation is not complete yet.
    ///
    virtual void init() override;

private:
    void select_resource();

    library_actions prompt_library_actions();

    resource_actions prompt_resource_actions();

    note_actions prompt_note_actions();

    void perform_library_actions();

    void perform_resource_actions(unsigned int const);

    void perform_note_actions(unsigned int const, unsigned int const);

    void view_note(unsigned int const);

    void export_note(std::shared_ptr<note>);

private:
    console _stream;
    std::filesystem::path _data_path;
    std::vector<std::string> _note_actions;
    std::vector<std::string> _resource_actions;
    std::vector<std::string> _library_actions;
    std::vector<std::shared_ptr<resource>> _resources;
};

} // flashback
