SET search_path TO "public";

create or replace function concat(text,text) returns text as
'select $1 || $2' language sql strict immutable;

create or replace function concat(text,text,text) returns text as
'select $1 || $2 || $3' language sql strict immutable;

create or replace function concat(text,text,text,text) returns text as
'select $1 || $2 || $3 || $4' language sql strict immutable;

create or replace function concat(text,text,text,text,text) returns text as
'select $1 || $2 || $3 || $4 || $5' language sql strict immutable;
