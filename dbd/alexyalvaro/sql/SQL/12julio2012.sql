-- EJERCICIO1
alter table cita add momento check(momento = 'mañana' or momento = 'tarde' );

--EJERCICIO2
alter table servicio add precio not null;

--EJERCICIO3
create or replace
function ejercicio3(pcodigo habitacion.codigo%type, pfecha date) return costar.tarifa%type
is
  auxcoste number;

begin
  select tarifa into auxcoste
  from costar, cita, calendario
  where habitacion.codigo = pcodigo and pfecha = calendario.fecha;

  return auxcoste;
  
end;

--EJERCICIO4
create or replace 
function ejercicio4( pcodigo servicio.codigo%tpye, pfecha date, pmomento cita.momento%type) return number
is
  
  cursor c1 is
    select * from empleado
    where pcodigo = servicio.codigo;
      
  auxempleados number;
  auxcontador number;
begin
  
  auxcontador := 0;
  auxempleados := 0;
  
  for creg in c1 loop
  
    select count(*) into auxcontador 
    from servicio, cita, cliente
    where pfecha = cita.fecha and pmomento = cita.momento
          and cliente is not null;
          
    if auxcontador = 0 then
      auxempleados := auxempleados + 1;
    end if;
  
  end loop;

  return auxempleados;
  
end;


--EJERCICIO5
create or replace
procedure ejercicio5(pcodigo servicio.codigo%tpye, pfecha date)
is

  cursor c1 is
    select * from empleado
    where servicio.codigo = pcodigo;
    
  auxmomento cita.momento%type;

begin

  for r in c1 loop
    
    select cita.momento into auxmomento
    from cita, cliente
    where cita.fecha = pfecha and cliente is null;
    
    if auxmomento = 'mañana' then
      escribir('empleado' || creg.nombre ||'mañana');
    end if;
    
    if auxmomento = 'tarde' then
      escribir('empleado' || creg.nombre ||'tarde');
    end if;
    
    if auxmomento = 'todo el dia' then
      escribir('empleado' || creg.nombre ||'todo el dia');
    end if;
    
  end loop;

end;


-- EJERCICIO6

