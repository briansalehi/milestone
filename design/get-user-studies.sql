select r.id as resource_id, r.name as resource, count(sc.id) as incomplete_sections, max(st.updated) as last_update
from flashback.resources r
join flashback.sections sc on sc.resource_id = r.id and sc.state = 'writing'
left join flashback.studies st on st.section_id = sc.id and st.user_id = 1
group by r.id, r.name
order by max(st.section_id) desc nulls first, r.id;

select sc.id, sc.headline, count(n.id) as notes, st.updated
from flashback.sections sc
join flashback.notes n on n.resource_id = sc.resource_id
left join flashback.studies st on st.section_id = sc.id and st.user_id = 1
where sc.resource_id = 15 and sc.state = 'writing'
group by sc.id, sc.headline, st.updated
order by st.updated desc nulls first, sc.id;

select n.id, n.heading, n.state, n.updated, n.creation
from flashback.sections sc
join flashback.notes n on n.resource_id = sc.resource_id
where sc.id = 4 and sc.state = 'writing'
order by sc.id;

