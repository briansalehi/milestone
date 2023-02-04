begin work;

create table if not exists resources (
    id integer generated always as identity,
    name varchar(200) not null,
    description varchar(500),
    purchase_link varchar(2000),
    creation_date datetime not null default now(),
    modification_date datetime,
    /* created_by integer references user (id), */
    primary key (id)
);

commit work;
