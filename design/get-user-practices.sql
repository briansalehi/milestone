drop function if exists flashback.get_user_subjects;
drop function if exists flashback.get_user_topics;
drop function if exists flashback.get_user_practices;
drop function if exists flashback.get_user_practice_blocks;

-- subjects which user should practice
create or replace function flashback.get_user_subjects(user_index integer)
returns table (id integer, name varchar(50), topics bigint, updated timestamp)
as $$
begin
    return query
    select s.id, s.name, count(t.*) as topics, p.updated
    from flashback.subjects s
    join flashback.topics t on t.subject_id = s.id
    left join flashback.progress p on p.topic_id = t.id and p.user_id = user_index
    group by s.id, s.name, p.updated
    order by p.updated desc nulls first, count(t.*) desc, s.id;
end; $$ language plpgsql;
alter function flashback.get_user_subjects owner to flashback;

-- topics of the subject chosen by user
create or replace function flashback.get_user_topics(user_index integer, subject_index integer)
returns table (subject_id integer, topic_id integer, name varchar(100), practices bigint, updated timestamp)
as $$
begin
    return query
    select s.id as subject_id, t.id as topic_id, t.name, count(pr.*) as practices, p.updated
    from flashback.subjects s
    join flashback.topics t on t.subject_id = s.id
    join flashback.practices pr on pr.topic_id = t.id
    left join flashback.progress p on p.topic_id = t.id and p.user_id = user_index
    where s.id = subject_index
    group by s.id, t.id, t.name, p.updated
    order by p.updated desc nulls first, count(pr.*) desc, s.id, t.id;
end; $$ language plpgsql;
alter function flashback.get_user_topics owner to flashback;

-- practices of the topic chosen by user
create or replace function flashback.get_user_practices(user_index integer, topic_index integer)
returns table (id integer, heading varchar(400), updated timestamp)
as $$
begin
    return query
    select pr.id, pr.heading, p.updated
    from flashback.practices pr
    left join flashback.progress p on p.topic_id = pr.topic_id and p.user_id = user_index
    where pr.topic_id = topic_index
    order by p.updated desc nulls first, pr.id;
end; $$ language plpgsql;
alter function flashback.get_user_practices owner to flashback;

-- blocks of practices under user selected topic
create or replace function flashback.get_user_practice_blocks(user_index integer, topic_index integer)
returns table (practice_id integer, block_id integer, heading varchar(400), block text, type flashback.block_type, language varchar(10), updated timestamp)
as $$
begin
    return query
    select pr.id as practice_id, b.id as block_id, pr.heading, b.content, b.type, b.language, p.updated
    from flashback.practices pr
    join flashback.practice_blocks b on b.practice_id = pr.id
    left join flashback.progress p on p.topic_id = pr.topic_id and p.user_id = user_index
    where pr.topic_id = topic_index
    order by p.updated desc nulls first, pr.id, b.id;
end; $$ language plpgsql;
alter function flashback.get_user_practice_blocks owner to flashback;
