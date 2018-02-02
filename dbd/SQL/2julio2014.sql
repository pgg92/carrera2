-- EJERCICIO4

create or replace
trigger ejercicio4
before insert on linea
for each row
declare

begin
  if :new.frecuenciaMin > 60 then
    raise_application_error(-20000, ' La linea ' ||:new.descripcion ||' esta mal
      planificada. su frecuencia no puede ser ' ||:new.frecuenciaMin);
  elsif :new.frecuenciaMin > 40 then
  end if;

end;