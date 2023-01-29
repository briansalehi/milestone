begin work;

create table if not exists reference_list (
    id integer generated always as identity,
    value varchar(2000) not null,
    practice integer references practices(id),
    creation_date date not null default date(now()),
    /* created_by integer references user (id), */
    primary key (id)
);

commit work;
