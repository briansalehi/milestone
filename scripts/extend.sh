#!/usr/bin/env bash

#---
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/users.sql"
#---

#---
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/create-note.sql"
#psql -U flashback -d flashback -c "create temp table temp_blocks (t_content text, t_type flashback.block_type, t_language varchar(10)); call create_note('Resource Test', 'Section Test', 'Heading Test');"
#---

#---
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/create-resource.sql"
#psql -U flashback -d flashback -c "create temp table temp_sections (t_headline varchar(100), t_reference varchar(2000)); call create_resource('Resource Test', 'website', 'Reference Test');"
#---

#---
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/create-practice.sql"
#psql -U flashback -d flashback -c "create temp table temp_blocks (t_content text, t_type flashback.block_type, t_language varchar(10)); call create_practice('Subject Test', 'Topic Test', 'Practice Heading Test');"
#---

#---
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/set-section-as-complete.sql"
#psql -U flashback -d flashback -c "call set_section_as_complete('Resource Test', 'Section Test'); select state from flashback.resources r join flashback.sections s on s.resource_id = r.id where r.name = 'Resource Test' and s.headline = 'Section Test';"
#---

#---
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/get-user-practices.sql"
#---

#---
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/get-user-studies.sql"
#---

exit
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/add-note-block.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/add-note-reference.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/add-practice-block.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/add-practice-reference.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/edit-note-block.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/edit-note-heading.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/edit-practice-block.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/edit-practice-headline.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/merge-duplicate-resources.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/merge-note-blocks.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/merge-practice-blocks.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/remove-note-reference.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/remove-reference-from-practice.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/rename-resource.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/rename-section-headline.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/rename-subject.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/rename-topic.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/split-note-block.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/split-practice-block.sql"
psql -U flashback -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/users.sql"
