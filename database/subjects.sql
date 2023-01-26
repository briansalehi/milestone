begin work;

create table if not exists subjects (
    id integer generated always as identity,
    title varchar(50) not null,
    primary key (id)
);

create or replace function get_resource_list (
    in user_id integer
)
returns table (
    subject_id integer,
    subject_title varchar(50)
)
{
}

commit work;
