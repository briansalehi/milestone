begin work;

create table if not exists resources (
    id integer generated always as identity,
    name varchar(15) not null,
    description varchar(120),
    primary key (id)
);

commit work;
