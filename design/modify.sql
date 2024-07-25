alter table if exists flashback.resource_sections rename to sections;
alter table if exists flashback.sections add column reference varchar(2000) default null;
