create or replace procedure create_note(
    resource_name varchar(1000),
    section_name varchar(100),
    heading varchar(400)
)
language plpgsql
as $$
declare resource_index integer;
declare section_index integer;
declare note_index integer;
declare block_index integer;
declare record record;
begin
    select r.id into resource_index from flashback.resources r where r.name = resource_name;
    select s.id into section_index from flashback.sections s where s.headline = section_name and s.resource_id = resource_index;
    insert into flashback.notes (resource_id, heading) values (resource_index, heading) returning id into note_index;
    insert into flashback.note_resources (note_id, section_id) values (note_index, section_index);
    raise notice 'New note % in section % from resource % created', note_index, section_index, resource_index;
    insert into flashback.note_blocks (note_id, content, type, language) select note_index, content, type, language from temp_note_blocks;
    delete from temp_note_blocks;
end;
$$;

