create or replace function get_resource_id(resource_name varchar(1000)) returns integer as $$
declare resource_id integer;
begin
    select id into resource_id from flashback.resources where name = resource_name;
    return resource_id;
end;
$$ language plpgsql;


create or replace procedure create_note(
    resource_name varchar(1000),
    section_name varchar(100),
    heading varchar(400),
    content varchar(2000),
    type flashback.block_type,
    language varchar(10)
)
language plpgsql
as $$
declare resource_id integer;
declare section_id integer;
declare note_id integer;
begin
    select r.id into resource_id from flashback.resources r where r.name = resource_name;
    select s.id into section_id from flashback.sections s where s.headline = section_name and s.resource_id = resource_id;
    insert into flashback.notes (resource_id, heading) values (resource_id, heading) returning id into note_id;
    insert into flashback.note_blocks (note_id, content, type, language) values (note_id, content, type, language);
    insert into flashback.note_resources (note_id, section_id) values (note_id, section_id);
    raise notice 'New note with index % created.', note_id;
end;
$$;
