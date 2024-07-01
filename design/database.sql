\c template1

drop database if exists flashback;
create database flashback;

drop schema if exists flashback;
create schema flashback authorization flashback_importer;

\c flashback;

set role to flashback_importer;

create table flashback.subjects (
    id int generated always as identity,
    name varchar(50) not null,
    creation timestamp not null default now(),
    updated timestamp not null default now(),
    primary key(id)
);

create table flashback.topics (
    id int generated always as identity,
    subject_id int,
    name varchar(100) not null,
    creation timestamp not null default now(),
    update timestamp not null default now(),
    primary key (id),
    constraint fk_subject foreign key (subject_id) references flashback.subjects(id) on update cascade on delete set null
);

create table flashback.practices (
    id int generated always as identity,
    topic_id int,
    heading varchar(400) not null,
    creation timestamp not null default now(),
    updated timestamp not null default now(),
    primary key (id),
    constraint fk_topics foreign key (topic_id) references flashback.topics(id) on update cascade on delete set null
);

create type flashback.block_type as enum ('text', 'code');

create table flashback.practice_blocks (
    id int generated always as identity,
    practice_id int,
    content text,
    type flashback.block_type not null default 'text',
    language varchar(10) not null,
    updated timestamp not null default now(),
    primary key (id),
    constraint fk_practice_block foreign key (practice_id) references flashback.practices(id) on update cascade on delete cascade
);

create type flashback.resource_type as enum ('unknown', 'book', 'link', 'video');

create table flashback.resources (
    id int generated always as identity,
    practice_id int,
    origin varchar(2000) not null,
    type flashback.resource_type not null default 'unknown',
    updated timestamp not null default now(),
    primary key (id),
    constraint fk_practice_resource foreign key (practice_id) references flashback.practices(id) on update cascade on delete cascade
);

create table flashback.references (
    id int generated always as identity,
    practice_id int,
    origin varchar(2000) not null,
    type flashback.resource_type not null default 'unknown',
    updated timestamp not null default now(),
    primary key (id),
    constraint fk_practice_reference foreign key (practice_id) references flashback.practices(id) on update cascade on delete cascade
);

