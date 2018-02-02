-- 2015 -- 2016
-- 30 junio 2016 Asociacion deportivo.

-- Es un procedimiento asociado a una operacion sobre una tabla.

-- 2.
set serveroutput on format;

create or replace
trigger ejercicio2
before insert or update of asociacion on equipo
for each row
declare
  numEntrenadores number;  
  nombreAsociacion asociacion.nombre%type;
  cursor centrenadores is
    select * from entrenador;
begin
  dbms_output.put_line(:new.asociacion || ' ' || :new.codigo || ' ' || :new.nombre);
  -- cuantos entrenadores pertenece a la nueva asociacion. :new.asociacion
  select count(*) into numEntrenadores from entrenador where asociacion = :new.asociacion;
  select nombre into nombreAsociacion from asociacion where codigo = :new.codigo;
  -- 
  if numEntrenadores = 0 then
    raise_application_error(-20000, 'la asociacion ' || numEntrenadores || ' no tiene entrenadores');
  else
    for creg in centrenadores loop
      if creg.nivel = :new.nivel then
        insert into responsable values(:new.codigo, creg.nif);
      end if;
    end loop;
  end if;
end;

select * from entrenador;
insert into equipo values ('3333', 'jose', 12, 'abcd');
update equipo set asociacion = 'eeee' where nombre = 'jose';

-- 30 de junio 2015
-- 4.
create or replace
trigger proveedorPrecio
before insert or update on suministrar
for each row
declare
  pprecio precio.pvp%type;
  pnombre proveedor.nombre%type;
begin
  -- sacar el precio del articulo del articulo que vamos a suministrar.
  select pvp into pprecio from articulo where :new.articulo = codigo;
  select nombre into pnombre from proveedor where :new.proveedor = nif;
  if :new.precio > pprecio then
    raise_application_error(-20000, pnombre ||  ' ' || :new.articulo || ' ' || :new.precio || ' ' || pprecio); 
  end if;
end;

-- 8 de julio 2013. 
-- 5.
create or replace
trigger vigilar_estado
before update of estado on material
for each row
declare
  descripcion tipo.descripcion%type;
begin
  select descripion into descripcion from tipo where :new.tipo = codtipo;
  if :new.estado = 'optimo' and :old.estado = 'pesimo' then
    dbms_output.put_line(' el material ' || :new.codigo || ' que es ' || pdescripcion || ' ha pasado...');
  end if;
end;

-- EJERCICIO6
create or replace 
trigger ejercicio6
before insert or update on suministrar
for each row
declare
  ptarifa tipo.tarifadiaria%type;
begin
  -- sacamos la tarifa diaria del tipo.
  select tarifadiaria into ptarifa from tipo where codtipo = :new.tipo;
  
  if :new.precio > ptarifa * 100 then
    raise_aplication_error(-2000, 'precio muy elevado');
  elsif :new.precio < ptarifa * 100 then
    update tipo set tarifadiaria = tarifadiaria * 0.9 where :new.tipo = codtipo;
  end if;
end;