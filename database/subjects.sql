begin work;

create table if not exists subjects (
    id integer generated always as identity,
    title varchar(50) not null,
    creation_date datetime not null default now(),
    modification_date datetime,
    /* created_by integer references users (id), */
    primary key (id)
);

commit work;
