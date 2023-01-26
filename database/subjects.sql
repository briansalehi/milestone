begin work;

create table if not exists subjects (
    id integer generated always as identity,
    title varchar(50) not null,
    primary key (id)
);

commit work;
