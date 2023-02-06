create or replace function search_resource ( iname varchar(200))
returns table (
    id integer,
    name varchar(200),
    description varchar(500),
    link varchar(5000),
    created timestamp
) as
$$
begin
    select id, name, description, creation_date
    from resources
    where to_tsvector(name) @@ to_tsquery();
end
$$
language plpgsql;
