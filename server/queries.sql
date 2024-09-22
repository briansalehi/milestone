-- user::resources
select * from get_user_studying_resources(1) order by subject_id, last_study asc nulls first, incomplete_sections desc, resource_id;
select * from get_user_editing_resources(1) order by subject_id, last_study asc nulls first, incomplete_sections desc, resource_id;
-- user::resources.sections.notes.blocks
select * from get_resource_study_notes(0) order by section_number, note_id;
select * from get_resource_editing_notes(0) order by section_number, note_id;
-- user::resource.sections
select * from get_user_sections(1, 0) order by updated asc nulls first, section_number asc;
-- user::resource.section.notes
select * from get_user_notes(1, 0) order by state asc, updated asc nulls first, heading asc;
-- user::resource.section.note.blocks
select * from get_user_note_blocks(1, 0) order by note_id asc, pos asc, updated asc;
-- user::subjects
select * from get_user_subjects(1) order by updated asc nulls first, topics desc, name asc;
-- user::subject.topics
select * from get_user_topics(1, 0) order by updated asc nulls first, topic_position asc, practices desc, topic_id asc;
-- user::subject.topic.practices
select * from get_user_practices(1, 0) order by updated asc nulls first, pos asc, heading asc;
-- editor::resources
select * from get_editor_resources(1) order by updated desc nulls first, incomplete_sections desc, subject_id, resource_id;
