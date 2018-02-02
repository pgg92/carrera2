create or replace
procedure listar_clase(pclase clase.tipo%type) is
  descripcion clase.descripcion%type;
  cuantasReparaciones number;
  cursor c1 is
    select distinct(codigo), nombre
    from averia, vehiculo, reparar
    where codigo = averia and matricula = vehiculo and clase = pclase;
  cursor c2 is
    select * from vehiculo
    where clase = pclase;
  maximoPagosPendientes number;
  ExcepcionReparaciones exception;
begin
  select descripcion into descripcion from clase where tipo = pclase;
  
  dbms_output.put_line('codigo: ' || pclase || ' descripcion: ' || descripcion);
  cuantasReparaciones := 0;
  for creg in c1 loop
    dbms_output.put_line(creg.codigo || ' ' || creg.nombre);
    cuantasReparaciones := cuantasReparaciones + 1;
  end loop;
  if cuantasReparaciones = 0 then
    raise ExcepcionReparaciones;
  end if;
  select max(pagosPendientes) into maximoPagosPendientes from vehiculo;
  for creg in c2 loop
    if creg.pagosPendientes = maximoPagosPendientes then
      select count(*) into cuantasReparaciones from reparar where creg.matricula = vehiculo;
      if creg.pagasPendientes = cuantasReparaciones then
        update vehiculo set bloquear = 'S' where matricula = creg.matricula;
      end if;
    end if;
  end loop;
exception
  when ExcepcionReparaciones then
    dbms_output.put_line('No existen reapraciones');
  when no_data_found then
    dbms_output.put_line('No existe la clase de vehiculo ' || pclase);
end;