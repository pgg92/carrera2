-- parcial 1

-- 1
create or replace function peligro(valorP material.peligroambiental%type) return number is
  
  contenedores number := 0;
  
begin
  
  select count(codigo) into contenedores from contenedor,distribuir,material where contenedor.codigo = distribuir.contenedor and
  contenedor.material = material.identificador and peligroambiental = valorP and peso > 300;
  
  return contenedores;
end;

-- 2
create or replace procedure pesomaximo(capacidadP contenedor.capacidad%type, pesoP distribuir.peso%type) is
  
  cursor c1 is select * from contenedor where capacidad = capacidadP;
  
  contenedorSel contenedor.codigo%type;
  
  cursor c2 is select * from distribuir where contenedor = contenedorSel;
  
  suma number;
  
begin
  
  for creg1 in c1 loop
    
    contenedorSel := creg1.codigo;
    suma := 0;
    
    for creg2 in c2 loop
      
      suma := suma + creg2.peso;
    end loop;
    
    if(suma > pesoP) then
      
      dbms_output.put_line('El contenedor ' || contenedorSel || ' de capacidad ' || capacidadP || ' ha alcanzado un peso maximo de ' || suma);
      update contenedor
      set clasificado = 'S'
      where codigo = contenedorSel;
    end if;
  end loop;
end;

-- parcial 2

-- 1

alter table padecer modify maxtemperatura not null;
alter table padecer modify maxtemperatura check(between 35 and 42);

-- 2
alter table infancia add foreign key(codigo) references enfermedad;

-- 4
update enfermedad
set edadfrecuente = edadfrecuente + 1
where añoaparece = 2000;

-- 6
create or replace function funcion1(codigoP animal.codigo%type, temperaturaP padecer.maxtemperatura%type) return animal.nombre%type is
    
  nombreAnimal animal.nombre%type;
  
  contador number := 0;
  
begin
  
  select count(animal) into contador from padecer where codigoP = animal and temperaturaP > maxtemperatura;
  
  if(contador > 0) then
  
    select nombre into nombreAnimal from animal where codigoP = codigo;
  
  else 
    
    nombreAnimal := 'Este animal no se ha encontrado en esa situacion';
  end if;
  
  return nombreAnimal;
  
end;

-- 7
create or replace procedure procedimiento1(añoP enfermedad.añoaparece%type) is
  
  cursor c1 is select enfermedad.codigo codigoE, enfermedad.nombre nombreE, animal.codigo codigoA, animal.nombre nombreA,fnacimiento from enfermedad,padecer,animal 
  where añoaparece = añoP and enfermedad = enfermedad.codigo and animal = animal.codigo;
  
  media number := 0;
  
begin
  
  for creg1 in c1 loop
    
    dbms_output.put_line(creg1.codigoE || ' ' || creg1.nombreE || ' ' || creg1.codigoA || ' ' || creg1.nombreA);
    
    select avg(fnacimiento) into media from animal,padecer where codigo = animal and creg1.codigoE = enfermedad;
    
    update enfermedad
    set edadfrecuente = media
    where codigo = creg1.codigoE;
    
    if(creg1.fnacimiento < 3) then
      
      insert into infancia(enfermedad)
      values(creg1.codigoE);
    end if;

-- parcial 3

-- 1
alter table perro modify codigo check(like 'A%' or like 'P%' or like 'M%');

-- 2
alter table escuela modify nombre not null;
alter table escuela modify unique(nombre);

-- 5
update escuela
set presupuesto = presupuesto + 100
where nivel > 8;

-- 7
create or replace procedure procedimietno1(razaP perro.raza%type,nivelP escuela.nivel%type) is
  
  cursor c1 is select * from perro where razaP = raza;
  
  perroSel perro.codigo%type;
  
  cursor c2 is select * from acudir,escuela where escuela = codigo and perroSel = perro;
  
begin
  
  for creg1 in c1 loop
    
    perroSel := creg1.codigo;
    
    dbms_output.put_line(perroSel || ' ' || creg1.nombre || ' ' || 'ASISTE A');
    
    for creg2 in c2 loop
      
      dbms_output.put_line(creg2.nombre || ' ' || creg2.codigo);
      
      update escuela
      set nivel = nivelP
      where codigo = creg2.codigo;
    end loop;
  end loop;
end;
  
-- final 1

-- 1
alter table cita modify momento check('MAÑANA' or 'TARDE');

-- 2
alter table servicio modify precio not null;

-- 3
create or replace function funcion1(codigoP habitacion.codigo%type, fechaP calendario.fecha%type) return habitacion.tarifa%type is
  
  tarifahabitacion habitacion.tarifa%type;
  
begin
  
  select tarifa into tarifahabitacion from reservar_habitacion,habitacion,tipo,costar
  where habitacion = codigo and nombre = habitacion.tipo and nombre = costar.tipo and calendario = fechaP and codigoP = codigo;
  
  return tarifahabitacion;
end;

-- 4
create or replace function servicio_disponible(codigoP servicio.codigo%type, fechaP cita.fecha%type, momentoP cita.momento%type) return number is
  
  empleados number := 0;
  codigoServicio servicio.codigo%type;
  cursor c1 is select * from empleado,realizar,cita where realizar.empleado = nif and cita.empleado = nif;

begin
  
  select codigo into codigoServicio from servicio where codigoP = codigo;
  
  for creg1 in c1 loop
    
    if(creg1.fecha != fechaP and creg1.momento != momentoP and creg1.codigo = codigoServicio) then
      
      empleados = empleado + 1;
    end if;
  end loop;
  
  return empleados;
  
exception
  
  when no_data_found when
    return -1;
end;

-- 5
create or replace procedure procedimeitno1(codigoP servicio.codigo%type,fechaP cita.fecha%type) is
  
  cursor c1 is select * from empleado,realizar where nif = empleado and codigoP = servicio;
  
  contadorManyana number := 0;
  contadorTarde number := 0;
  contadorEmpleados number := 0;
  
begin
  
  for creg1 in c1 loop
  
    select count(*) into contadorManyana from cita where fecha = fechaP and empleado = creg1.nif and momento = 'MAÑANA';
    select count(*) into contadorTarde from cita where fecha = fechaP and empleado = creg1.nif and momento = 'TARDE';
    
    if(contadorManyana = 0 and contadorTarde = 0) then
      
      dbms_output.put_line(creg1.nif || ' ' || 'TODO EL DIA');
      contadorEmpleados = contadorEmpleados + 1;
    elsif(contadorManyana = 0 and contadorTarde > 0) then
      
      dbms_output.put_line(creg1.nif || ' ' || 'MAÑANA');
      contadorEmpleados = contadorEmpleados + 1;
    elsif(contadorTarde = 0 and contadorManyana > 0) then
      
      dbms_output.put_line(creg1.nif || ' ' || 'TARDE');
      contadorEmpleados = contadorEmpleados + 1;
    end if;
  end loop;
  
  if(contadorEmpleados = 0) then
    
    update servicio
    set observaciones = 'AUMENTAR PERSONAL'
    where codigo = codigoP;
  end if;
end;

-- final 2

-- 1
alter table material modify estado check('OPTIMO' OR 'NORMAL' OR 'GASTADO' OR 'PESIMO');

-- 2
alter table cliente modify telefono not null;

-- 3
create or replace function funcion1(codigoP material.codigo%type) return tipo.tarifadiaria%type is
  
  tarifa tipo.tarifadiaria%type;
  
begin
  
  select tarifadiario into tarifa from material,tipo where codigo = tipo and codigoP = codigo;
  
  return tarifa;
end;

-- 4
create or replace procedure comprobar(codigoP material.codigo%type,fechaP calendario.fecha%type) is
  
  cursor c1 is select * from material where estado <> 'pesimo';
  tipoMaterial material.tipo%type;
  estadoAux material.estado%type;
  contador number;
  contador2 number := 0;
begin
    
    select estado into estadoAux from material where codigo = codigoP;
    select count(material) into contador from alquilar where fecha = fechaP;
    select codtipo into tipoMaterial from tipo,material where tipo = codtipo and codigoP = codigo;
    
    if(contador = 0) then
      
      if(estadoAux <> 'pesimo') then
        
        dbms_output.put_line('Se puede reservar');
      end if;
    end if;
    
    if(contador > 0) then
      
      for creg1 in c1 loop
        
        if(creg1.tipo = tipoMaterial) then
          
          select count(material) into contador from alquilar where fecha = fechaP and material = creg1.codigo;
          
          if(contador = 0) then
            
            contador2 = contador2 + 1;
            dbms_output.put_line(creg1.codigo || ' ' || creg1.estado);
          end if;
        end if;
      end loop;
      
      if(contador2 = 0) then
        
        dbms_output.put_line('Sin disponibilidad');
        
        update tipo
        set comentario = 'Muy demandado'
        where codtipo = tipoMaterial;
      end if;
    end if;
end;

-- final 3

-- 1
alter table autobus modify unique(matricula);
alter table autobus modify matricula not null;

-- 2
create or replace function funcio1(codigoP linea.codigo%type) return number is
  
  numero number;
  codigoLinea linea.codigo%type;
  
begin
  
  select codigo into codigoLinea from linea where codigoP = codigo;
  
  select count(codigo) into numero from autobus where linea = codigoP;
  
  return numero;

exception
  
  when no_data_found then
    dbms_output.put_line('No existe tal linea');
end;

-- 3
create or replace procedure procedimietno1(codigoP linea.codigo%type) is
  
  cursor c1 is select * from autobus where linea = codigoP;
  
begin
  
  update autobus
  set kmUltimaRevision = kmUltimaRevision + 1000;
  where linea = codigoP;
  
  for creg1 in c1 loop
    
    if(creg1.kmUltimaRevision > 100000) then
      
      dbms_output.put_line(creg1.matricula);
    end if;
  end loop;
end;

-- 5
create or replace procedure procedimiento2(codigoP linea.codigo%type) is
  
  cursor c1 is select * from recorrer,parada where parada = numero and linea = codigoP
  order by numero;
  
  paradaSel parada.codigo%type;
  
  cursor c2 is select * from linea,recorrer where linea = codigo and paradaSel = parada;
  
  numero number;
  
begin
  
  for creg1 in c1 loop
    
    dbms_output.put_line(creg1.direccion);
    
    select count(linea) into numero from recorrer where parada = creg1.parada;
    
    update parada
    set correspondencias = numero
    where numero = creg1.parada;
    
    paraSel = creg1.parada;
      
      for creg2 in c2 loop  
        
        dbms_output.put_line(creg2.codigo);
      end loop;
  end loop;
end;
    
  end loop;
end;

-- final 4

-- 1
alter table tipo-interes modify unique(nombre);
alter table tipo-interes modify nombre not null;

-- 2
update articulo
set cantidad = 0
where descripcion like '%NOVEDAD%' or like '%NUEVO%';

-- 3
create or replace procedure procedimiento1(valor number,tope number) is
  
  cursor c1 is select * from categoria;
  
  categoriaSel categoria.codigo%type;
  
  cursor c2 is select * from articulo where categoria = categoriaSel;
  contador number;
  cuantos number;
  
begin
  
  for creg1 in c1 loop
    
    categoriaSel := creg1.codigo;
    dbms_output.put_line(creg1.descripcion);
    contador := 0;
    
    for creg2 in c2 loop
      
      if(creg2.pvp + (creg2.pvp * valor/100) > tope) then
      
        dbms_output.put_line(creg2.codigo || ' ' || creg2.descripcion || ' ' || creg2.pvp);
        contador := contador + 1;
      end if;
      
    end loop;
    
    if(contador = 0) then
      
      dbms_output.put_line('NINGUNO');
    
    else
      
      select count(codigo) into cuantos from articulo where pvp + (pvp * valor/100) > tope);
      
      insert into lujo(codigo,descripcion,cantidad)
      values(categoriaSel,creg1.descripcion,cuantos);
      
  end loop;
end;

-- final 5

-- 1
create or replace function ejercicio1(codigoP equipo.codigo%type) return number is
  
  cursor c1 is select * from jugar,equipo where codigoP = equipo1 and codigo = equipo2;
  cursor c2 is select * from jugar,equipo where codigoP = equipo2 and codigo = equipo1;
  
  puntuacio number := 0;
  codigoSel equipo.codigo%type;
  contador number;
  ExcepcionJugar exception;
  nivelAux equipo.nivel%type;
  
begin
  
  select codigo into codigoSel from equipo where codigoP = codigo;
  select count(*) into contador from jugar where codigoP = equipo1 or codigoP = equipo2;
  select nivel into nivelAux from equipo where codigo = codigoP;
  
  if(contador = 0) then
    
    raise ExcpecionJugar;
  end if;
  
  for creg1 in c1 loop
    
    if(creg1.goles1 = creg1.goles2) then
      
      puntuacion := puntuacion + 0.5;
    
    elsif(creg1.goles1 > creg1.goles2) then
      
      if(nivelAux > creg1.nivel) then
        
        puntuacion := puntuacion + 1;
      
      elsif(nivelAux = creg1.nivel) then
        
        puntuacion := puntuacion + 2;
      
      elsif(nivelAux < creg1.nivel) then
        
        puntuacion := puntuacio + 3;
      end if;
    end if;
  end loop;
  
  for creg2 in c2 loop
    
    if(creg2.goles1 = creg2.goles2) then
      
      puntuacion := puntuacion + 0.5;
    
    elsif(creg2.goles1 < creg2.goles2) then
      
      if(nivelAux > creg2.nivel) then
        
        puntuacion := puntuacion + 1;
        
      elsif(nivelAux = creg2.nivel) then
        
        puntuacion := puntuacion + 2;
        
      elsif(nivelAux < creg2.nivel) then
        
        puntuacion := puntuacion + 3;
        
      end if;
    end if;
  end loop;
  
  return puntuacion;
  
exception
  
  when no_data_found then
    dbms_output.put_line('No esta ostia');
  when ExcepcionJugar then
    dbms_output.put_line('noooooooooooo');
    
end;

-- 3
create or replace procedure procedimiento1(x number) is
  
  cursor c1 is select count(equipo) cuantos,nif,nombre,nivel,asociacion from entrenador left join responsable(entrenador.nif = responsable.entrenador)
  group by nif,nombre;
  
  entrenadorSel entrenador.nif%type;
  
  cursor c2 is select * from equipo,responsable where equipo = codigo and entrenadorSel = entrenador;
  
  cuantos number;
  cuantosAux number;
  contador number := 0;
  
  cursor c3 is select count(codigo) algo from asociacion left join equipo(asociacion.codigo = equipo.asociacion);
  
  ExcepcionEquipos exception;
  
begin
  for creg3 in c3 loop
    
    if(algo >= x) then
      
      contador := contador + 1;
    end if;
  end loop;
  
  if(contador = 0) then
    
    raise ExcepcionEquipos;
    
  else
  
    for creg1 in c1 loop
      
      if(creg1.cuantos < x) then
        
        entrenadorSel := creg1.nif;
        
        dbms_output.put_line(creg1.nif || ' ' || creg1.nombre || ' ' creg1.cuantos);
        
        for creg2 in c2 loop
          
          select count(entrenador) into cuantos from responsable equipo = creg2.codigo;
          
          dbms_output.put_line(creg2.codigo || ' ' || creg2.nombre || ' ' || creg2.cuantos);
          
        end loop;
      end if;
      
      if(creg1.cuantos = 0) then
        
        dbms_output.put_line(creg1.nif || ' ' || creg1.nombre || ' ' creg1.cuantos);
        
        select count(codigo) into cuantosAux from entrenador,responsable,equipo where nif = entrenador and  equipo = codigo and creg1.nivel = equipo.nivel and
        equipo.asociacion = creg1.asociacion;
        
        insert into libre(entrenador,nombre,total)
        values(creg1.nif,creg1.nombre,cuantosAux);
      
      end if;
        
    end loop;
  end if;
  
exception
  
  when ExcepcionEquipos then
    dbms_output.put_line('No hay asociaciones con ' || x || ' o mas equipos');
end;
        
  