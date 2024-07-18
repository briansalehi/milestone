#!/usr/bin/env bash

psql -U flashback -d flashback -i design/modify.sql
psql -U flashback -d flashback -i design/users.sql
