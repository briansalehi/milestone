#pragma once

namespace flashback
{

///
/// \brief Components Spliting Program into Different Sections
///
/// Spaces are logical separations of the program each having different purposes.\n
/// For example, in one space user will be able to review their books and read
/// through their books further more, and in another space user will be able to
/// find their way through becoming an expert by learning specific subjects
/// step by step.
///
/// \section spaces Spaces
///
/// \startuml
/// !theme cyborg
/// left to right direction
/// actor "User" as user
/// actor "Author" as author
/// actor "Admin" as admin
/// package "Space Library" {
///     usecase "Search for a resource" as search
///     usecase "Select a resource" as select
///     usecase "Add a resource" as add
///     usecase "Edit a resource" as edit
///     usecase "Remove a resource" as remove
/// }
///
/// user --> search : user permission
/// user --> select : user permission
///
/// author --> add #line:red;line.bold;text:red : author permission
/// author --> edit #line:red;line.bold;text:red : author permission
///
/// admin --> remove #line:maroon;line.bold;text:maroon : admin permission
/// \enduml
///
class space
{
public:
    virtual void init() = 0;

protected:
    virtual char prompt_space_actions() = 0;
    virtual void perform_space_actions() = 0;
};

} // flashback
