--EJERCICIO1
ALTER TABLE tipointeres ADD( nombre tipointeres.nombre UNIQUE);
ALTER TABLE tipointeres ADD( nombre tipointeres.nombre NOT NULL);
--EJERCICIO2
UPDATE articulo
SET cantidad = 0
WHERE articulo.descripcion LIKE 'NOVEDAD'
AND articulo.descripcion LIKE 'NUEVO';
--EJERCICIO3
CREATE OR REPLACE PROCEDURE ejercicio3(
    pvalor NUMBER,
    ptope  NUMBER)
IS
  auxcateogira categoria.codigo;
  -- categorias que se encuentran en articulos
  CURSOR c1
  IS
    SELECT DISTINCT categoria INTO auxcategoria, descripcion FROM arituclo;
  CURSOR c2
  IS
    SELECT * FROM articulo WHERE articulo.categoria = auxcategoria;
  auxcomprobar NUMBER;
BEGIN
  auxcontador := 0;
  FOR r IN c1
  LOOP
    dmbs_output.put_line(c1.categoria || 'descripcion: ' || c1.descripcion);
    FOR s IN c2
    LOOP
      IF pvalor + c2.pvp > tope THEN
        dmbs_output.put_line(c2.codigo || c2.descripcion || c2.pvp);
        auxcomprobar := auxcomprobar + 1;
      END IF;
      IF auxcomprobar = 0 THEN
        dmbs_output.put_line('NINGUNO');
      ELSE
        INSERT
        INTO lujo
          (
            codcategoria,
            descripcion,
            cantidad
          )
          VALUES
          (
            c2.categoria,
            c2.descripcion,
            comprobar
          );
      END IF;
    END LOOP;
  END LOOP;
END;


--EJERCICIO4 (MIO)
CREATE OR REPLACE TRIGGER ejercicio4 before
  INSERT OR
  UPDATE ON suministrar FOR EACH row DECLARE auxnombreprov proveedor.nombre%type;
  auxprecio suministrar.pvp%type;
  CURSOR c1
  IS
    SELECT pvp,proveedor FROM suministrar WHERE articulo = :new.articulo;
BEGIN
  auxprecio := 100000;
  FOR r IN c1
  LOOP
    IF r.pvp         < auxprecio THEN
      auxprecio     := r.pvp;
      auxnombreprov := r.proveedor;
    END IF;
  END LOOP;
  IF :new.precio < 10 THEN
    INSERT INTO suministrar VALUES
      (auxnombreprov, :new.articulo, auxprecio
      );
  ELSE
    raise_application_error(-2000, 'El pvp del articulo no es menor que 10');
  END IF;
END;

--EJERCICIO4(NUSE)
CREATE OR REPLACE TRIGGER ejercicio4 before
  INSERT OR
  UPDATE ON suministrar FOR EACH row DECLARE auxprecio articulo.pvp%type;
  auxnombreprov proveedor.nombre%type;
  BEGIN
    -- precio del articulo a suministrar
    SELECT pvp
    INTO auxprecio
    FROM articulo
    WHERE :new.arituclo = arituclo.codigo;
    -- nombre del proveedor a mostrar
    SELECT proveedor.nombre
    INTO auxnombreprov
    FROM proveedor
    WHERE proveedor.cod = :new.proveedor;
    IF :new.precio      > auxprecio THEN
      raise_application_error(-2000, 'El proveedor ' || auxnombreprov || ' no puede suministrar el articulo ' || :new.articulo || ' a ' || :new.precio || ' euros, ya que su pvp es ' || auxprecio);
    END IF;
  END;
