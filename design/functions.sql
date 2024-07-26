drop procedure if exists create_note;
drop procedure if exists create_resource;

-- pre: there should be a temp_note_blocks temporary table
-- post: temp_note_blocks temporary table will be cleared
create or replace procedure create_note(
    resource_name varchar(1000),
    section_name varchar(100),
    heading varchar(400)
)
as $$
declare resource_index integer;
declare section_index integer;
declare note_index integer;
declare block_index integer;
declare record record;
begin
    select r.id into resource_index from flashback.resources r where r.name = resource_name;
    select s.id into section_index from flashback.sections s where s.headline = section_name and s.resource_id = resource_index;
    insert into flashback.notes (section_id, heading) values (section_index, heading) returning id into note_index;
    insert into flashback.note_blocks (note_id, content, type, language) select note_index, t_content, t_type, t_language from temp_note_blocks;
    delete from temp_note_blocks;
end; $$ language plpgsql;

-- pre: there should be a temp_sections temporary table
-- post: temp_sections temporary table will be cleared
create or replace procedure create_resource(
    name_string varchar(2000),
    type_string flashback.resource_type,
    resource_reference varchar(2000) default null
)
as $$
declare resource_index integer;
begin
    insert into flashback.resources (name, reference, type) values (name_string, resource_reference, type_string) returning id into resource_index;
    insert into flashback.sections (resource_id, headline, reference) select resource_index, headline_string, reference_string from temp_sections;
    delete from temp_sections;
end; $$ language plpgsql;

