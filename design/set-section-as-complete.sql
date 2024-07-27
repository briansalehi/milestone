create or replace procedure set_section_as_compelete (
    resource_name varchar(1000),
    section_headline varchar(100)
)
as $$
declare resource_index integer;
declare section_index integer;
begin
    select id into resource_index from flashback.resources where name = resource_name;
    select id into section_index from flashback.sections where resource_id = resource_index and headline = section_headline;
    update flashback.sections set state = 'completed' where id = section_index;
end; $$ language plpgsql;
