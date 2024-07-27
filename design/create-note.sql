drop procedure if exists create_note;

create temp table if not exists temp_note_blocks ();

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

