begin work;

create table if not exists resources (
    id integer generated always as identity,
    name varchar(200) not null,
    description varchar(500),
    purchase_link varchar(2000),
    full_coverage bool not null default false,
    primary key (id)
);

commit work;
