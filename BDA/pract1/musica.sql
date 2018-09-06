-- QUERIES USING 1 RELATION

-- Exercise 1
SELECT COUNT(*)
FROM disco;

-- Exercise 2
SELECT nombre
FROM grupo
WHERE pais <> 'España';

-- Exercise 3
SELECT titulo
FROM cancion
WHERE duracion > 5;

-- Exercise 4
SELECT DISTINCT funcion
FROM pertenece
ORDER BY funcion;

-- Exercise 5
SELECT nombre, num
FROM club
ORDER BY num;

-- Exercise 6
SELECT nombre, sede
FROM club
WHERE num > 500;


-- QUERIES USING MORE THAN 1 RELATION

-- Exercise 7
SELECT c.nombre, c.sede, g.nombre
FROM club c, grupo g
WHERE c.cod_gru = g.cod
AND g.pais = 'España';

-- Exercise 8
SELECT a.nombre
FROM artista a, grupo g, pertenece p
WHERE a.dni = p.dni
AND g.cod = p.cod
AND g.pais = 'España'
ORDER BY a.nombre;

-- Exercise 9
SELECT DISTINCT d.nombre
FROM disco d, esta e, cancion c
WHERE d.cod = e.cod
AND c.cod = e.can
AND c.duracion > 5
ORDER BY d.nombre;

-- Exercise 10
SELECT c.titulo
FROM disco d, esta e, cancion c
WHERE d.cod = e.cod AND e.can = c.cod
AND c.titulo = d.nombre
ORDER BY c.titulo;

-- Exercise 11
SELECT c.nombre, c.dir
FROM disco d, companyia c
WHERE d.cod_comp = c.cod
AND d.nombre LIKE 'A%';

-- Exercise 12
SELECT DISTINCT p1.dni
FROM pertenece p1, pertenece p2
WHERE p1.dni = p2.dni
AND p1.cod <> p2.cod;


-- QUERIES WITH SUBQUERIES

-- Exercise 13
SELECT nombre
FROM disco
WHERE cod_gru IN (
    SELECT cod
    FROM grupo
    WHERE fecha = (
        SELECT MIN(fecha)
        FROM grupo
    )
);

-- Exercise 14
SELECT nombre
FROM disco
WHERE cod_gru IN (
    SELECT cod_gru
    FROM club
    WHERE num > 5000
);

-- Exercise 15
SELECT nombre, num
FROM club
WHERE num = (
    SELECT MAX(num)
    FROM club
);

-- Exercise 16
SELECT titulo, duracion
FROM cancion
WHERE duracion = (
    SELECT MAX(duracion)
    FROM cancion
);


-- QUERIES WITH UNIVERSAL QUANTIFICATION

-- Exercise 17
SELECT nombre
FROM companyia
WHERE cod NOT IN (
    SELECT cod_comp
    FROM disco
    WHERE cod_gru IN (
        SELECT cod
        FROM grupo
        WHERE pais = 'España'
    )
);

-- Exercise 18
SELECT nombre
FROM companyia
WHERE cod IN (
    SELECT cod_comp
    FROM disco
    WHERE cod_gru IN (
        SELECT cod
        FROM grupo
        WHERE pais = 'España'
    )
) AND cod NOT IN (
    SELECT cod_comp
    FROM disco
    WHERE cod_gru IN (
        SELECT cod
        FROM grupo
        WHERE pais <> 'España'
    )
);

-- Exercise 19
SELECT nombre, dir
FROM companyia
WHERE cod IN (
    SELECT cod_comp
    FROM disco d1
    WHERE cod_gru IN (
        SELECT cod
        FROM grupo
        WHERE cod IN (
            SELECT cod_gru
            FROM disco d2
            WHERE d1.cod_comp = d2.cod_comp
        )
    )
) ORDER BY nombre;


-- QUERIES WITH GROUP BY

-- Exercise 20
SELECT g.nombre, SUM(c.num) FANS
FROM grupo g, club c
WHERE g.cod = c.cod_gru
AND g.pais = 'España'
GROUP BY g.nombre;

-- Exercise 21
SELECT nombre, COUNT(DISTINCT dni) MIEMBROS
FROM grupo, pertenece
WHERE grupo.cod = pertenece.cod
GROUP BY nombre
HAVING COUNT(DISTINCT dni) > 2;

-- Exercise 22
SELECT grupo.nombre, COUNT(disco.cod) DISCOS
FROM grupo, disco
WHERE grupo.cod = disco.cod_gru
GROUP BY grupo.nombre;

-- Exercise 23
SELECT companyia.nombre, COUNT(can) CANCIONES, dir
FROM companyia 
    LEFT JOIN (esta 
        NATURAL JOIN disco)
    ON companyia.cod = disco.cod_comp
GROUP BY companyia.nombre, dir
ORDER BY nombre;


-- OTHER QUERIES

-- Exercise 24
SELECT DISTINCT nombre
FROM artista
WHERE dni IN (
    SELECT dni
    FROM pertenece
    WHERE cod IN (
        SELECT grupo.cod
        FROM grupo LEFT JOIN club ON grupo.cod = club.cod_gru
        WHERE num > 500
        AND pais = 'Inglaterra'
    )
) ORDER BY nombre;

-- Exercise 25
SELECT titulo
FROM cancion LEFT JOIN esta ON cancion.cod = esta.can
WHERE esta.cod IN (
    SELECT disco.cod
    FROM disco
    WHERE cod_gru = (
        SELECT cod
        FROM grupo
        WHERE nombre = 'U2'
    )
) ORDER BY titulo;

-- Exercise 26
SELECT a1.nombre VOZ, a2.nombre GUITARRA
FROM pertenece p1, pertenece p2, artista a1, artista a2, grupo g1, grupo g2
WHERE p1.cod <> p2.cod
AND g1.cod = p1.cod
AND g2.cod = p2.cod
AND g1.pais = 'España'
AND g2.pais = g1.pais
AND a1.dni = p1.dni
AND a2.dni = p2.dni
AND p1.funcion = 'voz'
AND p2.funcion = 'guitarra';

-- Exercise 27
SELECT DISTINCT nombre
FROM artista, pertenece p1, pertenece p2
WHERE artista.dni = p1.dni
AND artista.dni = p2.dni
AND p2.cod <> p1.cod;

-- Exercise 28
SELECT titulo, duracion
FROM cancion
WHERE 1 = (
    SELECT COUNT(DISTINCT cod)
    FROM cancion
    WHERE duracion >= ALL (
        SELECT duracion
        FROM cancion
    )
) AND duracion >= ALL (
    SELECT duracion
    FROM cancion
);

-- Exercise 29
SELECT nombre, num
FROM club c1
WHERE 10 = (
    SELECT COUNT(DISTINCT cod)
    FROM club c2
    WHERE c2.num >= c1.num
);

-- Exercise 30
SELECT nombre
FROM artista LEFT JOIN pertenece p USING (dni)
WHERE funcion = 'bajo'
AND dni NOT IN (
    SELECT dni
    FROM pertenece
    WHERE p.cod <> cod
    AND funcion = 'bajo'
) AND 2 < (
    SELECT COUNT(dni)
    FROM pertenece
    WHERE p.cod = cod
) ORDER BY nombre;

-- Exercise 31
SELECT companyia.nombre, COUNT(can) CANCIONES
FROM companyia
    LEFT JOIN (disco
        LEFT JOIN esta
        USING (cod))
    ON companyia.cod = disco.cod_comp
GROUP BY companyia.cod, companyia.nombre
HAVING COUNT(can) = (
    SELECT MAX(COUNT(can)) CANCIONES
    FROM companyia 
        LEFT JOIN (disco
            LEFT JOIN esta
            USING (cod))
        ON companyia.cod = disco.cod_comp
    GROUP BY companyia.cod
);