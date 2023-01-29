begin work;

create table if not exists subjects (
    id integer generated always as identity,
    title varchar(50) not null,
    creation_date date not null default date(now()),
    modification_date date,
    /* created_by integer references users (id), */
    primary key (id)
);

commit work;
