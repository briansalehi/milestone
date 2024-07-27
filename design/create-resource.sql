drop procedure if exists create_resource;

--drop table if exists temp_sections;
--create temp table temp_sections (t_headline varchar(100), t_reference varchar(2000));

-- pre: there should be a temp_sections temporary table
-- post: temp_sections temporary table will be cleared
create or replace procedure create_resource (
    name_string varchar(2000),
    type_string flashback.resource_type,
    resource_reference varchar(2000) default null
)
as $$
declare resource_index integer;
begin
    insert into flashback.resources (name, reference, type) values (name_string, resource_reference, type_string) returning id into resource_index;
    insert into flashback.sections (resource_id, headline, reference) select resource_index, t_headline, t_reference from temp_sections;
    delete from temp_sections;
end; $$ language plpgsql;

