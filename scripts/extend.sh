#!/usr/bin/env bash

psql -U flashback -d flashback -f design/modify.sql
psql -U flashback -d flashback -f design/users.sql
psql -U flashback -d flashback -f design/functions.sql

