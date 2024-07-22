select r.id as subject_id, r.name as resource, count(sc.id) as incomplete_sections, max(st.updated) as last_update
from flashback.resources r
join flashback.sections sc on sc.resource_id = r.id and sc.state = 'writing'
left join flashback.studies st on st.section_id = sc.id and st.user_id = 1
group by r.id, r.name
order by max(st.section_id) desc nulls first, r.id;

select sc.id, sc.headline, st.updated
from flashback.sections sc
left join flashback.studies st on st.section_id = sc.id and st.user_id = 1
where sc.resource_id = 15 and sc.state = 'writing'
order by st.updated desc nulls first, sc.id;

select r.name as resource, sc.headline as section, n.heading as note, string_agg(nb.content, E'\n\n') as content
from flashback.resources r
join flashback.sections sc on sc.resource_id = r.id
join flashback.note_resources nr on nr.section_id = sc.id
join flashback.notes n on r.id = nr.note_id
left join flashback.note_blocks nb on nb.note_id = n.id
left join flashback.studies st on st.section_id = sc.id and st.user_id = 1
where sc.state = 'open'
group by r.id, r.name, sc.headline, n.id, n.heading
order by r.id, sc.headline, n.id;
