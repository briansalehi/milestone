#pragma once

namespace flashback
{

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
///     :Initialize space;
/// case (Milestone)
///     :Initialize space;
/// case (Roadmap)
///     :Initialize space;
/// endswitch
/// end
/// \enduml
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
class library: public space
{
public:
    void export(std::shared_ptr<note>);

private:
};

} // flashback
