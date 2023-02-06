create or replace function search_resource ( iname varchar(200))
returns table (
    resource_id integer,
    resource_name varchar(200),
    resource_description varchar(500),
    resource_link varchar(5000),
    resource_creation_date timestamp
) as
$$
begin
    return query select id, name, description, purchase_link, creation_date
    from resources
    where lower(name) like '%' || lower(iname) || '%'
    order by name;
end
$$
language plpgsql;
