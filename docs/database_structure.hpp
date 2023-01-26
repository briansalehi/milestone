/// \page database_structure Database Structure
///
/// \section db_spaces Spaces (?)
///
/// - id: primary key
/// - name: varchar(15) not null
/// - description: varchar(120)
///
/// \section db_resources Resources
///
/// - id: primary key
/// - title: varchar(200) not null
///
/// \section db_notes Notes
///
/// - id: primary key
/// - title: varchar(1000) not null
/// - description: text
/// - position: varchar(20)
/// - collected: bool not null default false
/// - collectable: bool not null default true
/// - resource: foreign key (resources.id)
///
/// \section db_subjects Subjects
///
/// - id: primary key
/// - title: varchar(50)
///
/// \section db_topics Topics
///
/// - id: primary key
/// - title: varchar(50)
/// - subject: foreign key (subjects.id)
/// - order: int
///
/// \section db_practices Practices
///
/// - id: primary key
/// - question: varchar(500)
/// - answer: text
/// - last_usage: date
/// - elapsed_time: int
/// - topic: foreign key (topics.id)
/// - origin: foreign key (notes.id)
///
/// \section db_references References
///
/// - id: primary key
/// - value: varchar(2000)
/// - practice: foreign key (practices.id)
///