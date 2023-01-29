begin work;

create table if not exists notes (
    id integer generated always as identity,
    title varchar(10000) not null,
    description text,
    position varchar(20),
    collected bool not null default false,
    collectable bool not null default true,
    resource integer references resources(id),
    creation_date date not null default date(now()),
    modification_date date,
    /* created_by integer references user (id), */
    primary key (id)
);

commit work;
