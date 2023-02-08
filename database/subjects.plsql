begin work;

create table if not exists subjects (
    id integer generated always as identity,
    title varchar(50) not null,
    creation_date timestamp without time zone not null default now(),
    modification_date timestamp without time zone,
    /* created_by integer references users (id), */
    primary key (id)
);

commit work;
