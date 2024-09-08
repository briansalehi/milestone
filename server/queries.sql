-- user::resources
select * from get_user_resources(1) order by updated asc nulls first, incomplete_sections desc, subject_id, resource_id;
-- user::resource.sections
select * from get_user_sections(1, 0) order by pos;
-- user::resource.section.notes
select * from get_user_notes(1, 0) order by state asc, updated asc nulls first, heading asc;
-- user::subjects
select * from get_user_subjects(1) order by updated asc nulls first, topics desc, name asc;
-- user::subject.topics
select * from get_user_topics(1, 0) order by updated asc nulls first, topic_position asc, practices desc, topic_id asc;
-- user::subject.topic.practices
select * from get_user_practices(1, 0) order by updated asc nulls first, pos asc, heading asc;
-- editor::resources
select * from get_editor_resources(1) order by updated desc nulls first, incomplete_sections desc, subject_id, resource_id;
