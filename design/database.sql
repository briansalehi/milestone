drop database if exists flashback;
create database flashback;

drop table if exists flashback.subjects;

create table flashback.subjects (
    id int generated always as identity,
    name varchar(50) not null,
    creation timestamp with time zone not null default now(),
    updated timestamp with time zone not null default now(),
    primary key(id)
);

drop table if exists flashback.topics;

create table flashback.topics (
    id int generated always as identity,
    name varchar(100) not null,
    creation timestamp with time zone not null default now(),
    update timestamp with time zone not null default now(),
    primary key(id)
);

