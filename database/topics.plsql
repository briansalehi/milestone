begin work;

create table if not exists topics (
    id integer generated always as identity,
    title varchar(50) not null,
    subject integer references subjects(id),
    creation_date timestamp without time zone not null default now(),
    modification_date timestamp without time zone,
    /* created_by integer references users (id), */
    primary key (id)
);

commit work;
