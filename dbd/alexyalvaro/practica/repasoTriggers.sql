--2016

-- 2
create or replace trigger ejercicio2
before insert or update of asociacion on equipo
for each row
declare
  
  contador number;
  nombreAsociacion asociacion.nombre%type;
  cursor c1 is select * from entrenador;

begin
  
  select count(nif) into contador from entrenador where asociacion = :new.asociacion;
  select nombre into nombreAsociacion from asociacion where codigo = :new.asociacion;
  
  if(contador = 0) then
    
    raise_application_error(-20601,'La asociacion ' || nombreAsociacion || ' no tiene entrenadores');
  
  else
    
    for creg1 in c1 loop
      
      if(creg1.nivel = :new.nivel) then
        
        insert into responsables
        values(creg1.nif,:new.codigo);
      end if;
    end loop;
  end if;
end;

--julio 2013
-- 5
create or replace trigger ejercicio5
before update on material
for each row
declare
  
  descripcionAux tipo.descripcion%type;
begin
  
  select descripcion into descripcionAux from tipo where codtipo = :new.tipo;
  
  if(:new.estado = 'pesimo' and :old.estado = 'optimo') then
    
    raise_application_error(-20601,'El material ' || :new.codigo || ' que es ' || descripcion || ' ha pasado de optimo a pesimo. Estudiar el deterioro');
  end if;
end;

-- 6
create or replace trigger ejercicio6
before insert on suministrar
for each row
declare

  tarifadiariaAux tipo.tarifadiaria%type;

begin
  
  select tarifadiaria into tarifadiariaAux from tipo where codtipo = :new.tipo;
  
  if(precio > tarifadiariaAux * 200) then
    
    raise_application_error(-20601,'Precio muy elevado. No considerarlo');
    
  elsif(precio < tarifadiariaAux * 100) then
    
    update tipo
    set tariafadiaria = tarifadiaria * 0.9
    where codtipo = :new.tipo;
  end if;
end;

--julio 2014
-- 4

create or replace trigger ejercicio4
before insert on linea
for each row
begin
  
  if(:new.frecuenciaMin > 60) then
    
    raise_application_error(-20601,'La linea ' || :new.descripcion || ', esta mal planificada, su frecuencia no puede ser ' || :new.frecuencia);
  
  elsif(:new.frecuenciaMin > 40) then
    
    raise_application_error(-20601,'Se debe valorar si la linea ' || :new.descripcion || ' necesita mas autobuses');
  end if;
end;

--junio 2015
-- 4
create or replace trigger ejercici4
before insert on suministrar
for each row
declare
  
  nombreAux proveedor.nombre%type;
  pvpAux articulo.pvp%type;
begin
  
  if(:new.precio > pvp) then
    
    select nombre into nombreAux from proveedor where :new.proveedor = nif;
    select pvp into pvpAux from articulo where :new.articulo = codigo;
    raise_application_error(-20601,'El proveedor ' || nombreAux || ', no puede suministrar el articulo ' || :new.articulo || ' a ' || :new.precio ||
    ' euros, ya que su pvp es ' || pvpAux);
  end if;
end;

-- 5
create or replace trigger ejercicio5
before update or insert of cantidad on articulo
for each row
declare
  
  nombreProveedor proveedor.nombre%type;
  preciominimo number
begin
  
  if(:new.cantidad < 10) then
    
    select min(precio) into preciominimo from suministrar where articulo = :new.codigo;
    select nombre into nombreProveedor from proveedor,suministrar where nif = proveedor and precio = preciominimo;
    
    insert into solicitudes(codigo,nombreprov)
    values(:new.codigo,nombreProveedor);
  end if;
end;

--julio 2012
-- 6
create or replace trigger ejercicio6
before update or insert of cliente on cita
for each row
declare
  
  contador number;
  nombreCliente cliente.nombre%type;
begin
  
  select count(*) into contador from reserva_habitacion where cliente = :new.cliente and fecha = :new.fecha;
  
  if(contador = 0) then
  
    select nombre into nombreCliente from cliente where nif = :new.cliente;  
    raise_application_error(-20601,'El cliente ' || nombreCliente || ' no tiene reserva de habitacion en la fecha ' || :new.fecha);
  end if;
end;

-- 7
create or replace trigger bueno2
before insert on realizar_j
for each row
declare
  cuantosServicios number;
begin
   
   select count(*) into cuantosServicios from realizar;
   
   if(cuantosServicio = 4) then
    
    update empleado set especializar = 1 where nif = :new.empleado;
  end if;
end;

-- julio 2011
-- 8
create or replace trigger julio2011
before insert on padecer
for each row
declare

  anyo number;
  nombreAux enfermedad.nombre%type;
  contador number
  nombreAnimal animal.nombre%type;
begin
  
  select añoaparece into anyo from enfermedad where :new.enfermedad = codigo;
  
  if(anyo = to_char(sysdate, 'YYYY') then
    
    select nombre into nombreAux from enfermedad where :new.enfermedad = codigo;
    raise_application_error(-20601,'La enfermedad ' || nombreAux || ' es nueva. Consultar con el supervisor para estas altas');
  
  else
    
    if(:new.maxtemperatura < 40) then
      
      select count(codigo) into contador from termica where enfermedad = :new.enfermedad;
      
      if(contador > 0) then
        
        select nombre into nombreAnimal from animal where codigo = :new.animal;
        
        raise_application_error(-20601,'El animal ' || nombreAnimal || ' todavia puede tener fiebre mas alta. Estar alerta');
      end if;
    
    elsif :new.maxtemperatura > 40 then
      
      begin
        insert into termica values (:new.enfermedad);
      exception
        
        when dup_val_on_index then
        null;
      end;
    end if;
  end if;
end;
      
-- mayo 2009
-- 8
create or replace trigger hola8
before insert on darclase
for each row
declare
  nivelAux escuela.nivel%type;
  exclusivaAux profesor.exclusiva%type;
  nombreAux escuela.nombre%type;
begin
  
  select nivel into nivelAux from escuela where codigo = :new.escuela;
  select exclusiva into exclusivaAux from profesor where dni = :new.profesor;
  
  if(nivelAux < 5 and exclusivaAux != 'S') then
    
    select nombre into nombreAux from escuala where codigo = :new.escuela;
    raise_application_error(-20601,'La escuela de nombre ' || nombreAux || ' no puede tener profesores sin exclusiva');
  
  else
    
    if(nivelAux > 4 and :new.darclase > 5) then
      
      update profesor
      set exclusiva = 'S'
      where dni = :new.profesor;
    
    else
      
      update profesor
      set exclusiva = 'N'
      where dni = :new.profesor; 
    end if;
  end if;
end;

-- en relacion muchos a muchos siempre es insert
-- en relacion de muchos a uno insert update
-- control 3 de 2015
create or replace trigger ejercici1
before insert on reparar
for each row
declare
  nombreAux vehiculo.propietario%type;
  pagosAux vehiculo.pagosPendientes%type;
begin

  select propietario into nombreAux from vehiculo where matricula = :new.vehiculo;
  if(:new.importe > 500) then
    
    raise_application_error(-20601,'Hay que pedir autorizacion a ' || nombreAux || ', para reparar el vehiculo ' || :new.vehiculo);
    
  else
    
    select pagosPendientes into pagosAux from vehiculo where matricula = :new.vehiculo;
    if(:new.importe > 100 and pagosAux > 0) then
      
      begin
      insert into moroso
      values(:new.vehiculo,nombreAux);
      exception
        when dup_val_on_index then
          null;
      end;
      
      raise_application_error(-20601,'El propietario ' || nombreAux || ' tiene ' || pagosAux || ' facturas pendientes');
    end if;
  end if;
end;

  




  