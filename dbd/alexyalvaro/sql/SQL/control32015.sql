--EJERCICIO1
create or replace
trigger ejercicio1 before
insert or update on reparar
for each row
declare
 auxnombre vechiculo.nombre%type;
 auxmatricula vehiculo.matricula%type;
 auxpagos vehiculo.pagosPendientes&type;
 contador number;
begin

  select propietario into auxnombre from vehiculo
  where :new.matricula = vehiculo.matricula;

  if :new.importe > 500 then
    raise_application_error(-20000, 'hay que pedir autorizacion a ' || auxnombre || 
    'para reparar el vehiculo ' || :new.matricula);
  end if;
  
  select pagosPendientes into auxpagos from vehiculo
  where :new.matricula = vehiculo.matricula;
  
  select count(*) into contador from vehiculo
  where :new.matricula = vehiculo.matricula;
  
  if :new.importe > 100 and auxpagos > 0then
    insert moroso(:new.matricula,auxnombre);
    escribir('el propietario tiene ' || auxnombre || 'tiene ' || contador || 'facturas pendientes');
  end if;

end;

-- EJERCICIO2
create or replace
procedure ejercicio2(pclase clase.tipo%type)
is

begin

end;

