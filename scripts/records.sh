#!/usr/bin/env bash

while read -r record
do
    psql -U postgres -d flashback -f "$record"
done <<< "$(find /tmp/references/records -type f -name '*.sql')"
