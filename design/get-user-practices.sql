select s.name as subject, t.name as topic, pr.heading as practice, string_agg(pb.content, E'\n\n') as content
from flashback.practices pr
join flashback.topics t on pr.topic_id = t.id
join flashback.subjects s on s.id = t.subject_id
left join flashback.practice_blocks pb on pb.practice_id = pr.id
left join flashback.progress p on p.topic_id = t.id and p.user_id = 1
group by s.id, s.name, t.id, t.name, pr.id, pr.heading, pr.id, p.updated
order by p.updated desc nulls first, s.id, t.id, pr.id;
