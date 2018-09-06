/*
#####################
CREACIO DE LES TAULES
#####################
*/
-- si ja estan creades cal esborrar-les

DROP TABLE p2_Docencia CASCADE CONSTRAINT;
DROP TABLE p2_Departamento CASCADE CONSTRAINT;
DROP TABLE p2_Asignatura CASCADE CONSTRAINT;
DROP TABLE p2_Profesor CASCADE CONSTRAINT;



CREATE TABLE p2_Departamento (
	cod_dep CHAR(4) CONSTRAINT pk_departamento PRIMARY KEY DEFERRABLE,
	nombre VARCHAR2(50) NOT NULL,
	telefono CHAR(8),
	director CHAR(9) /* CONSTRAINT fk_departament_profesor REFERENCES p2_Profesor(dni) */
);

CREATE TABLE p2_Asignatura (
	cod_asg CHAR(5) CONSTRAINT pk_asignatura PRIMARY KEY DEFERRABLE,
	nombre VARCHAR2(50) NOT NULL UNIQUE,
	semestre CHAR(2) NOT NULL CHECK (semestre IN ('1A', '1B', '2A', '2B', '3A', '3B', '4A', '4B')),
	cod_dep CHAR(4) NOT NULL CONSTRAINT fk_asignatura_departamento REFERENCES p2_Departamento(cod_dep) DEFERRABLE,
	teoria FLOAT NOT NULL,
	practicas FLOAT NOT NULL,
	CHECK (teoria >= practicas)
);


CREATE TABLE p2_Profesor(
	dni CHAR(9) CONSTRAINT pk_profesor PRIMARY KEY DEFERRABLE,
	nombre VARCHAR2(80) NOT NULL,
	telefono CHAR(8),
	cod_dep CHAR(4) NOT NULL CONSTRAINT fk_profesor_departamento REFERENCES p2_Departamento(cod_dep) DEFERRABLE,
	provincia VARCHAR2(25),
	edad INTEGER
);


CREATE TABLE p2_Docencia(
	dni CHAR(9) CONSTRAINT fk_docencia_profesor REFERENCES p2_Profesor(dni) DEFERRABLE,
	cod_asg CHAR(5) CONSTRAINT fk_docencia_asignatura REFERENCES p2_Asignatura(cod_asg) DEFERRABLE,
	gteo INTEGER NOT NULL,
	gpra INTEGER NOT NULL,
	CONSTRAINT pk_docencia PRIMARY KEY (dni, cod_asg) DEFERRABLE
);

ALTER TABLE p2_Departamento ADD CONSTRAINT fk_departament_profesor FOREIGN KEY (director) REFERENCES p2_Profesor(dni) DEFERRABLE ;




/*
#####################
CREACIO DELS TRIGGERS
#####################

cal crear els triggers un a un

operacions que cal controlar:

- inserir en profesor
- modificar dni en docencia
- esborrar en docencia

- modificar dni en profesor no cal, per integritat referencial
DROP TRIGGER nombre_trigger;
*/

CREATE OR REPLACE TRIGGER R1_Ins_Profesor
AFTER INSERT ON p2_Profesor
DECLARE
  howmany NUMBER;
BEGIN
  SELECT COUNT(*) INTO howmany
  FROM p2_Profesor
  WHERE dni NOT IN (SELECT dni FROM p2_Docencia);
  IF howmany > 0 THEN
    RAISE_APPLICATION_ERROR (-20000, 'Tot Professor ha d''impartir doc?ncia');
  END IF;
END;


CREATE OR REPLACE TRIGGER R1_Del_Up_Docencia
AFTER DELETE OR UPDATE OF dni ON p2_Docencia
DECLARE
  howmany NUMBER;
BEGIN
  SELECT COUNT(*) INTO howmany
  FROM p2_Profesor
  WHERE dni NOT IN (SELECT dni FROM p2_Docencia);
  IF howmany > 0 THEN
    RAISE_APPLICATION_ERROR (-20000, 'Tot Professor ha d''impartir doc?ncia');
  END IF;
END;



select * from user_triggers;
select * from user_tables;
/*
#####################
INSERCIO D'INFORMACIO
#####################

*/

COMMIT;

SET CONSTRAINT fk_asignatura_departamento DEFERRED;
SET CONSTRAINT fk_departament_profesor DEFERRED;
SET CONSTRAINT fk_docencia_profesor DEFERRED;
SET CONSTRAINT FK_PROFESOR_DEPARTAMENTO DEFERRED;


DELETE FROM p2_departamento;
DELETE FROM p2_profesor;
DELETE FROM p2_docencia;
DELETE FROM p2_asignatura;


COMMIT;

SET CONSTRAINT fk_asignatura_departamento DEFERRED;
SET CONSTRAINT fk_departament_profesor DEFERRED;
SET CONSTRAINT fk_docencia_profesor DEFERRED;

INSERT INTO p2_Asignatura VALUES ('11545', 'Analisis Matematico', '1A', 'DMA', 4.5, 1.5);
INSERT INTO p2_Asignatura VALUES ('11546', 'Algebra', '1B', 'DMA', 4.5, 1.5);
INSERT INTO p2_Asignatura VALUES ('11547', 'Matematica Discreta', '1A', 'DMA', 4.5, 1.5);
INSERT INTO p2_Asignatura VALUES ('11548', 'Bases de Datos y Sistemas de Informacion', '3A', 'DSIC', 4.5, 1.5);


INSERT INTO p2_Departamento VALUES ('DLA', 'Linguistica Aplicada', 2255, 111);
INSERT INTO p2_Departamento VALUES ('DMA', 'Matematica Aplicada', 1256, NULL);
INSERT INTO p2_Departamento VALUES ('DSIC', 'Sistemas Informaticos y Computacion', 1542, 453);


INSERT INTO p2_Docencia VALUES (111, '11547', 1, 3);
INSERT INTO p2_Docencia VALUES (123, '11545', 0, 2);
INSERT INTO p2_Docencia VALUES (123, '11547', 1, 1);
INSERT INTO p2_Docencia VALUES (453, '11547', 2, 1);
INSERT INTO p2_Docencia VALUES (564, '11545', 2, 2);


INSERT INTO p2_Profesor VALUES (111, 'Luisa Bos Prez', NULL, 'DMA', 'Alicante', 33);
INSERT INTO p2_Profesor VALUES (123, 'Juana Cerda Perez', 3222, 'DMA', 'Valencia', 50);
INSERT INTO p2_Profesor VALUES (453, 'Elisa Rojo Amando', 7859, 'DSIC', 'Valencia', 26);
INSERT INTO p2_Profesor VALUES (564, 'Pedro Marti Garcia', 3412, 'DMA', 'Castellon', 27);


COMMIT;

select * from p2_Docencia;
select * from p2_Profesor;
select * from p2_Departamento;
select * from p2_Asignatura;

CREATE VIEW semestre1 AS
    SELECT *
    FROM p2_Asignatura
    WHERE semestre LIKE '1_';

select nombre from semestre1 where practicas >1;
