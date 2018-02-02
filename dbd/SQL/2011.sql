create or replace procedure get_item(nick inventory.idPlayer%type, objeto inventory.idItem%type, cantidad number(2)) is
capacidad number(2);
no_cabe exception;

begin
select count(*) into capacidad from inventory where inventory.idplayer=nick;
if (50-capacidad)>cantidad then
insert into inventory values(nick,objeto);
else
raise no_cabe;
end if;
exception
when no_cabe then escribir('No caben mas objetos de ese tipo.');
end;