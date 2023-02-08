begin work;

create table if not exists reference_list (
    id integer generated always as identity,
    value varchar(2000) not null,
    practice integer references practices(id),
    creation_date timestamp without time zone not null default now(),
    modification_date timestamp without time zone,
    /* created_by integer references user (id), */
    primary key (id)
);

commit work;
