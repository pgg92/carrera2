--EJERCICIO3
create or replace function ejercicio3(pcodigo material.codigo%type) return tipo.tarifadiaria%type
is
  auxtarifa tipo.tarifadiaria%type;

begin
  select tarifadiaria into auxtarifa from tipo
  where codigo = pcodigo and tipo = codtipo;
  
  return auxtarifa;
end;

--EJERCICIO4
create or replace procedure ejerccio4(pcodigo material.codigo%type, pfecha date)
is
  auxestado material.estado%type;
  auxcontador number;
  auxlistar number;
  
  cursor c1 is
    select * from material
    where estado = auxestado;
begin
  select estado into auxestado from mateiral
  where codigo = pcodigo;

  select count(*) into auxcontador from alquilar
  where material = pcodigo;

  if auxestado <> 'PESIMO' and auxontador = 0 then
    dmbs_output.put_line('Se puede reservar');
  end if;
  
  auxlistar := 0;
  if auxestado <> 'PESIMO' and auxontador <> 0 then
        
      for r in c1 loop
        dmbs_output.put_line(material.codigo || material.estado);
        auxlistar := auxlistar + 1;
      end loop;
      
      if auxlistar = 0 then
        dbms_out.put_line('sin disponibilidad');
        update tipo set comentario = 'muydemandado' where codtipo = a;
      end if;
      
  end if;

end;

--EJERCICIO5
CREATE OR REPLACE TRIGGER ejercicio5 before
  UPDATE OF estado ON material FOR EACH row
  
  DECLARE auxdescripcion tipo.descripcion%type;
  
  BEGIN
    SELECT descripcion
    INTO auxdescripcion
    FROM tipo
    WHERE tipo.codtipo = :new.tipo;
    
    IF :new.tipo = 'pesimo' AND :old.tipo = 'optimo' THEN
      raise_appplication_error('El material ' || :new.codigo ||' que es ' 
        || auxdescripcion ||' ha pasado directamente directamente                              
        de optimo a pesimo. Estudiar el deterioro' );
    END IF;
  END;
