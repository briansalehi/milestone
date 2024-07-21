select r.name as resource, sc.headline as section, n.heading as note, string_agg(nb.content, E'\n\n') as content
from flashback.resources r
join flashback.sections sc on sc.resource_id = r.id
join flashback.note_resources nr on nr.section_id = sc.id
join flashback.notes n on r.id = nr.note_id
join flashback.note_blocks nb on nb.note_id = n.id
group by r.id, r.name, sc.headline, n.id, n.heading
order by r.id, sc.headline, n.id;
