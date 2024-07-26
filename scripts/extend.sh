#!/usr/bin/env bash

psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/users.sql"
psql -U postgres -d flashback -f "$( readlink -f "$(dirname "$0")/.." )/design/functions.sql"

