begin work;

create table if not exists topics (
    id integer generated always as identity,
    title varchar(50) not null,
    subject integer references subjects(id),
    primary key (id)
);

commit work;
