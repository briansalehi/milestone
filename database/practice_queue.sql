begin work;

create view practice_queue as
select max(p.id) as id,
       substr(max(p.question), 0, 25) as question,
       t.id as tid,
       substr(t.title, 0, 25) as topic,
       date(max(p.last_usage)) as last_usage,
       max(p.elapsed_time) as elapsed_time,
       count(p.id) as pc
from practices p
inner join topics t on t.id = p.topic
group by (t.id, p.last_usage)
order by p.last_usage desc nulls first, t.id asc;

commit work;
