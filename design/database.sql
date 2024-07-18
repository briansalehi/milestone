﻿\c template1;

drop database if exists flashback;
drop schema if exists flashback;
drop role if exists flashback;

create role flashback login;
create schema flashback authorization flashback;
create database flashback with template template1 owner flashback;

set role to flashback;

\c flashback;

create type flashback.state as enum ('open', 'writing', 'completed', 'approved', 'released', 'ignored');

create table flashback.subjects (
    id int generated always as identity primary key,
    name varchar(50) not null unique,
    creation timestamp not null default now(),
    updated timestamp not null default now()
);

create table flashback.topics (
    id int generated always as identity primary key,
    subject_id int,
    name varchar(100) not null,
    creation timestamp not null default now(),
    update timestamp not null default now(),
    constraint fk_subject foreign key (subject_id) references flashback.subjects(id) on update cascade on delete set null
);

create table flashback.practices (
    id int generated always as identity primary key,
    topic_id int,
    heading varchar(400) not null,
    creation timestamp not null default now(),
    updated timestamp not null default now(),
    constraint fk_topics foreign key (topic_id) references flashback.topics(id) on update cascade on delete set null
);

create type flashback.block_type as enum ('text', 'code');

create table flashback.practice_blocks (
    id int generated always as identity primary key,
    practice_id int,
    content text,
    type flashback.block_type not null default 'text',
    language varchar(10) not null,
    updated timestamp not null default now(),
    constraint fk_practice_block foreign key (practice_id) references flashback.practices(id) on update cascade on delete cascade
);

create type flashback.resource_type as enum ('unknown', 'book', 'website', 'video', 'mailing list', 'manual');

create table flashback.resources (
    id int generated always as identity primary key,
    name varchar(1000) not null,
    reference varchar(2000),
    type flashback.resource_type not null default 'unknown',
    created timestamp not null default now(),
    updated timestamp not null default now()
);

insert into flashback.resources (name, reference, type) values
      ('https://www.youtube.com',                                               'https://youtube.com',        'video')
    , ('https://www.youtu.be',                                                  'https://youtube.com',        'video')
    , ('https://www.boost.org',                                                 'https://boost.org',          'website')
    , ('https://www.latex-tutorial.com',                                        'https://latex-tutorial.com', 'website')
    , ('https://www.qt.io',                                                     'https://qt.io',              'website')
    , ('GDB Tips by Greg Law',                                                   null,                        'website')
    , ('Daily C++ Bites',                                                        null,                        'mailing list')
    , ('C++ Daily Bites',                                                        null,                        'mailing list')
    , ('https://www.cppstories.com',                                            'https://www.cppstories.com', 'website')
    , ('https://en.cppreference.com',                                           'https://www.cppstories.com', 'website')
    , ('LinkedIn Course: C++ Design Patterns: Creational by Olivia Chiu Stone', 'https://www.linkedin.com',   'video')
    , ('mdadm(1)',                                                              'Unix Manual',                'manual')
    , ('Kevin Dankwardt''s Linux Device Drivers',                               null,                         'website')
    , ('LinkedIn Course: Linux Device Drivers',                                 'https://linkedin.com',       'video');

create table flashback.resource_sections (
    id int generated always as identity primary key,
    resource_id int,
    headline varchar(100) not null,
    state flashback.state not null default 'open',
    created timestamp not null default now(),
    updated timestamp not null default now(),
    constraint fk_resource_section foreign key (resource_id) references flashback.resources(id) on update cascade on delete cascade
);

create table flashback.notes (
    id int generated always as identity primary key,
    resource_id int,
    heading varchar(400) not null,
    state flashback.state not null default 'open',
    creation timestamp not null default now(),
    updated timestamp not null default now(),
    constraint fk_resource_note foreign key (resource_id) references flashback.resources(id) on update cascade on delete set null
);

create table flashback.note_blocks (
    id int generated always as identity primary key,
    note_id int,
    content text,
    type flashback.block_type not null default 'text',
    language varchar(10) not null,
    updated timestamp not null default now(),
    constraint fk_note_block foreign key (note_id) references flashback.notes(id) on update cascade on delete cascade
);

create table flashback.references (
    id int generated always as identity primary key,
    practice_id int,
    origin varchar(2000) not null,
    type flashback.resource_type not null default 'unknown',
    updated timestamp not null default now(),
    constraint fk_practice_reference foreign key (practice_id) references flashback.practices(id) on update cascade on delete cascade
);

create table flashback.note_references (
    id int generated always as identity primary key,
    note_id int,
    origin varchar(2000) not null,
    type flashback.resource_type not null default 'unknown',
    updated timestamp not null default now(),
    constraint fk_note_reference foreign key (note_id) references flashback.notes(id) on update cascade on delete cascade
);

create table flashback.practice_resources (
    id int generated always as identity primary key,
    practice_id int,
    section_id int,
    constraint fk_practice_resource foreign key (practice_id) references flashback.practices(id) on update cascade on delete cascade,
    constraint fk_practice_section foreign key (section_id) references flashback.resource_sections(id) on update cascade on delete cascade
);

create table flashback.note_resources (
    id int generated always as identity primary key,
    note_id int,
    section_id int,
    constraint fk_note_resource foreign key (note_id) references flashback.notes(id) on update cascade on delete cascade,
    constraint fk_note_section foreign key (section_id) references flashback.resource_sections(id) on update cascade on delete cascade
);

