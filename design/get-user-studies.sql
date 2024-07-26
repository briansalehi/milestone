drop function get_user_resources;
drop function get_user_sections;
drop function get_user_notes;
drop function get_user_note_blocks;

-- resources that user is studying
create or replace function get_user_resources(user_index integer)
returns table (id integer, resource varchar(1000), incomplete_sections bigint, updated timestamp)
as $$
begin
    return query
    select r.id, r.name, count(sc.id), max(st.updated)
    from flashback.resources r
    join flashback.sections sc on sc.resource_id = r.id and sc.state in ('open', 'writing')
    left join flashback.studies st on st.section_id = sc.id and st.user_id = user_index
    group by r.id, r.name;
end; $$ language plpgsql;

-- writing resource sections which user is writing notes for
create or replace function get_user_sections(user_index integer, resource_index integer)
returns table (id integer, headline varchar(100), notes bigint, updated timestamp)
as $$
begin
    return query
    select sc.id, sc.headline, count(n.id), st.updated
    from flashback.sections sc
    join flashback.notes n on n.section_id = sc.resource_id
    left join flashback.studies st on st.section_id = sc.id and st.user_id = user_index
    where sc.resource_id = resource_index and sc.state in ('open', 'writing')
    group by sc.id, sc.headline, st.updated;
end; $$ language plpgsql;

-- heading only notes written by user under a writing section
create or replace function get_user_notes(user_index integer, section_index integer)
returns table (id integer, heading varchar(400), state flashback.state, updated timestamp, creation timestamp)
as $$
begin
    return query
    select n.id, n.heading, n.state, n.updated, n.creation
    from flashback.sections sc
    join flashback.notes n on n.section_id = sc.id
    where sc.id = section_index and sc.state in ('open', 'writing');
end; $$ language plpgsql;

-- The full body of notes by which user is writing under a section
create or replace function get_user_note_blocks(user_index integer, section_index integer)
returns table (note_id integer, block_id integer, content text, type flashback.block_type, language varchar(10), updated timestamp)
as $$
begin
    return query
    select n.id, nb.id, nb.content, nb.type, nb.language, nb.updated
    from flashback.sections sc
    join flashback.notes n on n.section_id = sc.id
    join flashback.note_blocks nb on nb.note_id = n.id
    where sc.id = section_index and sc.state in ('open', 'writing');
end; $$ language plpgsql;
