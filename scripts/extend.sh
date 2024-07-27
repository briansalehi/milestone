#!/usr/bin/env bash

psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/users.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/create-note.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/create-resource.sql"

exit
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/add-note-block.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/add-note-reference.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/add-practice-block.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/add-practice-reference.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/create-practice.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/edit-note-block.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/edit-note-heading.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/edit-practice-block.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/edit-practice-headline.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/get-user-practices.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/get-user-studies.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/merge-duplicate-resources.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/merge-note-blocks.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/merge-practice-blocks.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/remove-note-reference.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/remove-reference-from-practice.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/rename-resource.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/rename-section-headline.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/rename-subject.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/rename-topic.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/split-note-block.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/split-practice-block.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/users.sql"
