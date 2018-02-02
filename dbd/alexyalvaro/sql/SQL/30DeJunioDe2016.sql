-- EXAMEN 30 DE JUNIO DE 2016 - PRUEBA B -
CREATE TABLE asociacion
  (
    codigo     CHAR(4) PRIMARY KEY,
    nombre     VARCHAR(40),
    destacados NUMBER(2)
  );
CREATE TABLE entrenador
  (
    nif        CHAR(9) PRIMARY KEY,
    nombre     VARCHAR(40),
    nivel      NUMBER(2) NOT NULL,
    asociacion CHAR(4) REFERENCES asociacion NOT NULL
  );
CREATE TABLE equipo
  (
    codigo     CHAR(4) PRIMARY KEY,
    nombre     VARCHAR(40),
    nivel      NUMBER(2) NOT NULL,
    asociacion CHAR(4) REFERENCES asociacion NOT NULL
  );
CREATE TABLE jugar
  (
    equipo1 CHAR(4) REFERENCES equipo,
    equipo2 CHAR(4) REFERENCES equipo,
    goles1  NUMBER(2),
    goles2  NUMBER(2),
    PRIMARY KEY(equipo1, equipo2)
  );
CREATE TABLE responsable
  (
    equipo     CHAR(4) REFERENCES equipo,
    entrenador CHAR(9) REFERENCES entrenador,
    PRIMARY KEY(equipo, entrenador)
  );
CREATE TABLE libre
  (
    entrenador CHAR(9) REFERENCES entrenador PRIMARY KEY,
    nombre     VARCHAR(40),
    total      NUMBER(3)
  );
-- 0. Funcion que dado el codigo de un equipo pasado como
-- parametro devuelva los goles totales que ese equipo ha metido.
-- El equipo puede jugar como local o como visitante,
-- lo indica el parametro mediante un char. (estado = 'L', locales
-- si estado = 'V' visitantes, si estado es 'T' todos si no -1.
-- si el equipo no existe mostrar el equipo no existe, con una excepcion.
-- si no mostrar el nombre del equipo y a continuacion los goles.
CREATE OR REPLACE FUNCTION obtener_goles
  (
    pequipo jugar.equipo1%type,
    estado CHAR
  )
  RETURN NUMBER
IS
  goles_local     NUMBER;
  goles_visitante NUMBER;
  goles_resultado NUMBER;
  nombre_equipo equipo.nombre%type;
BEGIN
  SELECT nombre INTO nombre_equipo FROM equipo WHERE pequipo = codigo;
  IF estado = 'L' THEN
    SELECT SUM(goles1) INTO goles_local FROM jugar WHERE equipo1 = pequipo;
    goles_resultado := goles_local;
  elsif estado       = 'V' THEN
    SELECT SUM(goles2) INTO goles_visitante FROM jugar WHERE equipo2 = pequipo;
    goles_resultado := goles_visitante;
  elsif estado       = 'T' THEN
    SELECT SUM(goles1) INTO goles_local FROM jugar WHERE equipo1 = pequipo;
    SELECT SUM(goles2) INTO goles_visitante FROM jugar WHERE equipo2 = pequipo;
    goles_resultado := goles_local + goles_visitante;
  ELSE
    goles_resultado := -1;
  END IF;
RETURN goles_resultado;
EXCEPTION
WHEN no_data_found THEN
  dbms_output.put_line('el equipo no existe');
END;
-- 0.1 Procedimiento en el que para el equipo pasado como parametro se muestren
-- los partidos en los cuales el total de goles supera al parametro, mostrar
-- primero los partidos como local y luego como visitante.
-- hacer dos cursores.
CREATE OR REPLACE PROCEDURE mostrar_superan(
    pequipo equipo.codigo%type,
    min_goles NUMBER)
IS
  CURSOR clocal
  IS
    SELECT * FROM jugar WHERE goles1 + goles2 > min_goles AND pequipo = equipo1;
  CURSOR cvisitante
  IS
    SELECT * FROM jugar WHERE goles1 + goles2 > min_goles AND pequipo = equipo2;
BEGIN
  FOR creg IN clocal
  LOOP
    dbms_output.put_line(creg.equipo1 || ' ' || creg.equipo2 || ' ' || creg.goles1 || creg.goles2);
  END LOOP;
  FOR creg IN cvisitante
  LOOP
    dbms_output.put_line(creg.equipo1 || ' ' || creg.equipo2 || ' ' || creg.goles1 || creg.goles2);
  END LOOP;
END;
-- 0.2 Procedimiento en el que para el equipo pasado como parametro muestre los
-- puntos que lleva, si gana +3, si empata +1.
CREATE OR REPLACE PROCEDURE obtener_puntos(
    pequipo equipo.codigo%type)
IS
  -- cursor.
  CURSOR c1
  IS
    SELECT * FROM jugar WHERE pequipo = equipo1 OR pequipo = equipo2;
  total_puntos NUMBER;
BEGIN
  total_puntos := 0;
  FOR creg IN c1
  LOOP
    IF pequipo      = creg.equipo1 AND creg.goles1 > creg.goles2 THEN
      total_puntos := total_puntos + 3;
    elsif pequipo   = creg.equipo1 AND creg.goles1 = creg.goles THEN
      total_puntos := total_puntos + 1;
    elsif pequipo   = creg.equipo2 AND creg.goles2 > creg.goles1 THEN
      total_puntos := total_puntos + 3;
    elsif pequipo   = creg.equipo2 AND creg.goles2 = creg.goles1 THEN
      total_puntos := total_puntos + 1;
    END IF;
  END LOOP;
  RETURN total_puntos;
END;
--1.
CREATE OR REPLACE FUNCTION ejericio1(
  pequipo equipo.codigo%type)
IS
  -- cursor donde para el equipo pasado como parametro, aparezcan los
  -- equipos a los cuales se ha enfrentado, goles y el nivel del equpo al que se enfrento.
BEGIN
  -- hacer una select para sacar el nivel del equipo pasado como parametro.
  -- hacer una select para comprobar si esta en la tabla jugar y si no
  -- esta lanzar una excepcion.
  --
END:

--Ejercicio 3
CREATE OR REPLACE PROCEDURE ejercicio3_nazi(
    x NUMBER)
IS
  -- CURSOR EN EL QUE APAREZCAN OADA ASOCIACION LA CANTIDAD DE EQUIPOS QUE
  -- PERTENECEN A DICHA ASOCIACION JUNTO CON EL CODIGO DE LA ASOCIACION
  auxasociacion asociacion.tipo%type;
  CURSOR casociacion
  IS
    SELECT asociacion
    INTO auxasociacion,
      COUNT(codigo)
    FROM equipo
    GROUP BY asociacion;
  -- CURSOR EN EL QUE PARA CADA ENTRENADOR SE MUESTRA, EL NIF, EL NOMBRE
  -- Y LA CANTIDAD DE EQUIPOS DE LOS CUALES ES RESPONSABLE. (INCLUIDO LOS
  -- QUE NO SON RESPONSABLE DE NINGUN EQUIPO
  CURSOR entrenador
  IS
    SELECT entrenador.nif,
      entrenador.nombre,
      cotun(responsable.equipo)
    FROM entrenador
    LEFT JOIN responsable
    ON entrenador.nif = responsable.etrenador
    GROUP BY entrenador.nif,
      entrenador.nombre;
  entrenadorSel entrenador.nif%type;
  -- CURSOR EN EL QUE PARA LOS EQUIPOS ENTRENADos POR UN ENTRENADOR CONRETO
  -- MUESTRE EL NOMBRE DEL EQUIPO, CODIGO Y LA CANTIDAD TOTAL DE SUS ENTRENADORES.
  CURSOR cequipos
  IS
    SELECT equipo.codigo ecodigo,
      equipo.nombre enombrem COUNT(responsable.entrenador)
    FROM equipo,
      responsable
    WHERE equipo.codigo        = responsable.codigo
    AND resopnsable.entrenador = entrenadorSel;
  cantidadEntrenadores       NUMBER;
  ExcepcionNoHayAsociaciones EXCEPTION;
  cantitdadSuperan           NUMBER;
BEGIN
  cantidadSuperan := 0;
  FOR creg IN asociacion
  LOOP
    IF creg.cantidad  >= x THEN
      cantidadSuperan := cantidadSuperan + 1;
    END IF;
  END LOOP;
  -- SI NO EXISTEN NINGUNA ASOCIACION QUE SUPERA ESA CANTIDAD
  IF cantidadSuperan = 0 THEN
    raise ExcepcionNoHayAsociaciones;
  END IF;
  FOR creg IN centrenadores
  LOOP
    dms_out.put_line(creg.enif ||' ' || creg.nombre || ' ' || creg.cantidad;
    -- OARA CADA ENTRENADOR HAY QUE MOSTRAR LOS EQUIPOS QUE ENTRENA
    IF creg.cantidad = 0 THEN
      -- SACAMOS TODOS LOS EQUIPOS QUE TIENEN EL MISMO NIVEL QUE EL ENTRENADOR
      --  Y CON LA MISMA ASOCIACION
      SELECT COUNT(*)
      INTO cantidadPodrian
      FROM equipo
      WHERE nivel    = creg.enivel
      AND asociacion = creg.asociacion;
    END IF;
    -- INSERTARLOS EL LIBRES
    inser INTO VALUES(creg.enif, creg.enombre, cantidadPodrian);
  elsif creg.cantidad < x THEN
    --MOSTRAR LOS EQUIPOS DE LOS QUE ES RESPONABLE
    entrenadorSel := creg.nif;
    FOR creg2 IN cequipos
    LOOP
      -- SACO LA CANTIDAD DE ENTRENADORES QUE TIENE EL EQUIPO CREG2.EQUIPO
      SELECT COUNT(*)
      INTO cantidadEntrenadores
      FROM responsable
      GROUP BY equipo;
      dbms_out.put_line( creg.cod || ' ' ||creg.nombre || ' ' || cantidadEntrenadores);
    END LOOP;
  END IF;
END
-- es un procedimiento asociado a una opreacion sobre una tabla
-- EJERCICIO2
CREATE OR REPLACE TRIGGER ejercicio2 before
  DELETE OR
  UPDATE OF asociacion ON equipo FOR EACH row DECLARE numentrenadores NUMBER;
  CURSOR c1
  IS
    SELECT * FROM entrenadores;
BEGIN
  -- num entrenadores que pertenecen a la asociacion
  SELECT COUNT(*)
  INTO numentrenadores
  FROM entrenador
  WHERE NEW:asociacion.codigo = entrenador.asociacion;
  IF numentrenadoes           = 0 THEN
    raise_application_error(-2000, 'La asociacion' || new.asociacion.codigo | 'no tiene entrenadores');
  END IF;
  IF numentrenadores <> 0 THEN
    FOR r IN c1
    LOOP
      IF r.nivel = :new.equipo.nivel THEN
        INSERT INTO responsable VALUES
          (:new.equipo.codigo, r.entrenador.nif
          );
      END IF;
    END LOOP;
  END IF;
END;
--EJERCICIO3
CREATE OR REPLACE PROCEDURE ejercicio3(px number)
IS

 cursor c1 is select * from entrenador;
  
 cursor c2 is select * from equipo
    where responsable.equipo = codigo
    and entrenador = r;

 auxcontador number;
 contador number;

BEGIN

  for r in c1 loop
  
    -- numero de equipos de los que es resposable un entrenador
    select count(*) into auxcontador from responsable
    where r.nombre = responsable.entrenador;
  
    -- recorrer los equipos de los que es resposable el entrenador
    contador := 0;
    while contador < auxcontador loop
      
    end loop;
  
  
    if auxcontador < px then
      dmbs_output.put_line('Entrenador: ' || r.nif  || r.nombre ||', resposable
        de: ' || auxcontador);
    
    end if;
  
  end loop;

END;

-- ejercicio1
CREATE OR REPLACE FUNCTION ejericio1(
  pequipo equipo.codigo%type)
  
IS
  cursor c1 is
    select goles1, goles2, equipo1, equipo2 from jugar
    where equipo1 = pcodigo or equipo2 = pcodigo;
    
  no_pertence exception  
BEGIN

  auxpuntuacion := 0;

  if c1 is not null then
  
    for r in c1 loop
      if r.goles1 = r.goles2 then
        auxpuntuacion := auxpuntiacion + 0.5;
        raise_application_error
      end if;
      if r.goles1 = 
    end loop;
    
  end if;
  
  if c1 is null then
  
  end if;

END:




crea or replace procedure get_item(nick inventory.idPlayer%type, objeto inventory.idItem%type, cantidad number(2)) is
declare
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





