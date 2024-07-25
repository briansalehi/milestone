drop function get_user_studying_resources;
drop function get_user_studying_sections;
drop function get_user_studying_notes;
drop function get_user_studying_note_blocks;

-- resources that user is studying
create or replace function get_user_studying_resources(user_index integer)
returns table (resource_id integer, resource varchar(1000), incomplete_sections bigint, updated timestamp)
as $$
begin
    return query
    select r.id as resource_id, r.name as resource, count(sc.id) as incomplete_sections, max(st.updated)
    from flashback.resources r
    join flashback.sections sc on sc.resource_id = r.id and sc.state = 'writing'
    left join flashback.studies st on st.section_id = sc.id and st.user_id = user_index
    group by r.id, r.name
    order by max(st.section_id) desc nulls first, r.id;
end; $$ language plpgsql;

-- writing resource sections which user is writing notes for
create or replace function get_user_studying_sections(user_index integer, resource_index integer)
returns table (id integer, headline varchar(100), notes bigint, updated timestamp)
as $$
begin
    return query
    select sc.id, sc.headline, count(n.id) as notes, st.updated
    from flashback.sections sc
    join flashback.notes n on n.resource_id = sc.resource_id
    left join flashback.studies st on st.section_id = sc.id and st.user_id = user_index
    where sc.resource_id = resource_index and sc.state = 'writing'
    group by sc.id, sc.headline, st.updated
    order by st.updated desc nulls first, sc.id;
end; $$ language plpgsql;

-- heading only notes written by user under a writing section
create or replace function get_user_studying_notes(user_index integer, section_index integer)
returns table (id integer, heading varchar(400), state flashback.state, updated timestamp, creation timestamp)
as $$
begin
    return query
    select n.id, n.heading, n.state, n.updated, n.creation
    from flashback.sections sc
    join flashback.note_resources ns on ns.section_id = sc.id
    join flashback.notes n on n.id = ns.note_id
    where sc.id = section_index and sc.state = 'writing'
    order by sc.id;
end; $$ language plpgsql;

-- The full body of notes by which user is writing under a section
create or replace function get_user_studying_note_blocks(user_index integer, section_index integer)
returns table (note_id integer, block_id integer, content text, type flashback.block_type, language varchar(10), updated timestamp)
as $$
begin
    return query
    select n.id as note_id, nb.id as block_id, nb.content, nb.type, nb.language, nb.updated
    from flashback.sections sc
    join flashback.note_resources ns on ns.section_id = sc.id
    join flashback.notes n on n.id = ns.note_id
    join flashback.note_blocks nb on nb.note_id = n.id
    where sc.id = section_index and sc.state = 'writing'
    order by sc.id;
end; $$ language plpgsql;
