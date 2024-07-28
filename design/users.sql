drop table if exists flashback.studies;
drop table if exists flashback.progress;
drop table if exists flashback.credentials;
drop table if exists flashback.users;
drop type if exists flashback.user_state;

create type flashback.user_state as enum ('active', 'deactivated', 'removed');
alter type flashback.user_state owner to flashback;

create table flashback.users (
    id int generated always as identity primary key,
    username varchar(20) unique not null,
    first_name varchar(30),
    middle_name varchar(30),
    last_name varchar(30),
    state flashback.user_state not null default 'active'
);
alter table flashback.users owner to flashback;

create table flashback.credentials (
    id int generated always as identity primary key,
    user_id int,
    hash varchar(4096) not null,
    updated timestamp not null default now(),
    constraint fk_user_credential_id foreign key (user_id) references flashback.users(id) on update cascade on delete cascade
);
alter table flashback.credentials owner to flashback;

create table flashback.progress (
    id int generated always as identity primary key,
    user_id int,
    topic_id int,
    updated timestamp not null default now(),
    constraint fk_user_progress_id foreign key (user_id) references flashback.users(id) on update cascade on delete cascade,
    constraint fk_user_topic_id foreign key (topic_id) references flashback.topics(id) on update cascade on delete cascade
);
alter table flashback.progress owner to flashback;

create table flashback.studies (
    id int generated always as identity primary key,
    user_id int,
    section_id int,
    updated timestamp not null default now(),
    constraint fk_user_studies_id foreign key (user_id) references flashback.users(id) on update cascade on delete cascade,
    constraint fk_user_section_id foreign key (section_id) references flashback.sections(id) on update cascade on delete cascade
);
alter table flashback.studies owner to flashback;

insert into flashback.users (username, first_name, last_name) values ('briansalehi', 'Brian', 'Salehi');
