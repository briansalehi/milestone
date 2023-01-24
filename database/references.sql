begin work;

create table if not exists reference_list (
    id integer generated always as identity,
    value varchar(2000) not null,
    practice integer references practices(id),
    primary key (id)
);

commit work;
