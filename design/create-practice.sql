drop procedure if exists flashback.create_practice;

--drop table if exists temp_blocks;
--create temp table if not exists temp_blocks (t_content text, t_type flashback.block_type, t_language varchar(10));

-- pre: there should be a temp_blocks temporary table
-- post: temp_blocks temporary table will be cleared
create or replace procedure flashback.create_practice (
    subject_name varchar(50),
    topic_name varchar(100),
    practice_heading varchar(400)
)
as $$
declare subject_index integer;
declare topic_index integer;
declare practice_index integer;
declare block_index integer;
begin
    select id into subject_index from flashback.subjects where name = subject_name;
    select id into topic_index from flashback.topics where name = topic_name and subject_id = subject_index;
    insert into flashback.practices (topic_id, heading) values (topic_index, practice_heading) returning id into practice_index;
    insert into flashback.practice_blocks (practice_id, content, type, language) select practice_index, t_content, t_type, t_language from temp_blocks;
    delete from temp_blocks;
end; $$ language plpgsql;

alter procedure flashback.create_practice owner to flashback;
