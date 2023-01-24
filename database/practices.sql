begin work;

create table if not exists practices (
    id integer generated always as identity,
    question varchar(500) not null,
    answer text,
    last_usage date,
    elapsed_time integer not null default 0,
    topic integer references topics (id),
    origin integer references notes (id),
    primary key (id)
);

commit work;
