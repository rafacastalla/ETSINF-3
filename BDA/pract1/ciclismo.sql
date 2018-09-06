-- QUERIES USING 1 RELATION

-- Exercise 1
SELECT codigo, tipo, color, premio
FROM maillot;

-- Exercise 2
SELECT dorsal, nombre
FROM ciclista
WHERE edad <= 25;

-- Exercise 3
SELECT nompuerto, altura
FROM puerto
WHERE categoria = 'E';

-- Exercise 4
SELECT netapa
FROM etapa
WHERE salida = llegada;

-- Exercise 5
SELECT COUNT(*)
FROM ciclista;

-- Exercise 6
SELECT COUNT(*)
FROM ciclista
WHERE edad > 25;

-- Exercise 7
SELECT COUNT(*)
FROM equipo;

-- Exercise 8
SELECT AVG(edad)
FROM ciclista;

-- Exercise 9
SELECT MIN(altura), MAX(altura)
FROM puerto;


-- QUERIES USING MORE THAN 1 RELATION

-- Exercise 10
SELECT nompuerto, categoria C
FROM puerto, ciclista
WHERE puerto.dorsal = ciclista.dorsal
AND nomeq = 'Banesto';

-- Exercise 11
SELECT nompuerto, puerto.netapa, km
FROM puerto, etapa
WHERE puerto.netapa = etapa.netapa;

-- Exercise 12
SELECT DISTINCT equipo.nomeq, director
FROM equipo, ciclista
WHERE equipo.nomeq = ciclista.nomeq
AND edad > 33;

-- Exercise 13
SELECT DISTINCT nombre, color
FROM ciclista c, llevar l, maillot m
WHERE c.dorsal = l.dorsal
AND l.codigo = m.codigo
ORDER BY nombre;

-- Exercise 14
SELECT DISTINCT c.nombre, e.netapa
FROM etapa e, ciclista c, llevar l, maillot m
WHERE e.dorsal = c.dorsal
AND c.dorsal = l.dorsal
AND l.codigo = m.codigo
AND color = 'Amarillo'
ORDER BY c.nombre;

-- Exercise 15
SELECT e.netapa
FROM etapa e, etapa e2
WHERE e2.netapa = e.netapa - 1
AND e2.llegada <> e.salida;


-- QUERIES WITH SUBQUERIES

-- Exercise 16
SELECT netapa, salida
FROM etapa
WHERE netapa NOT IN (
    SELECT netapa
    FROM puerto
);

-- Exercise 17
SELECT AVG(edad)
FROM ciclista
WHERE dorsal IN (
    SELECT dorsal
    FROM etapa
);

-- Exercise 18
SELECT nompuerto
FROM puerto
WHERE altura > (
    SELECT AVG(altura)
    FROM puerto
);

-- Exercise 19
SELECT salida, llegada
FROM etapa
WHERE netapa IN (
    SELECT netapa
    FROM puerto
    WHERE pendiente = (
        SELECT MAX(pendiente)
        FROM puerto
    )
);

-- Exercise 20
SELECT dorsal, nombre
FROM ciclista
WHERE dorsal IN (
    SELECT dorsal
    FROM puerto
    WHERE altura = (
        SELECT MAX(altura)
        FROM puerto
    )
);

-- Exercise 21
SELECT nombre
FROM ciclista
WHERE edad = (
    SELECT MIN(edad)
    FROM ciclista
);

-- Exercise 22
SELECT nombre
FROM ciclista
WHERE dorsal IN (
    SELECT dorsal
    FROM etapa
) AND edad = (
    SELECT MIN(edad)
    FROM ciclista
    WHERE dorsal IN (
        SELECT dorsal
        FROM etapa
    )
);

-- Exercise 23
SELECT nombre
FROM ciclista
WHERE 1 < (
    SELECT COUNT(nompuerto)
    FROM puerto
    WHERE dorsal = ciclista.dorsal
);


-- QUERIES WITH UNIVERSAL QUANTIFICATION

-- Exercise 24
SELECT DISTINCT netapa
FROM etapa
WHERE NOT EXISTS (
    SELECT *
    FROM puerto
    WHERE etapa.netapa = netapa
    AND altura <= 700
) AND EXISTS (
    SELECT *
    FROM puerto
    WHERE etapa.netapa = netapa
) ORDER BY netapa;

-- Exercise 25
SELECT nomeq, director
FROM equipo
WHERE NOT EXISTS (
    SELECT *
    FROM ciclista
    WHERE nomeq = equipo.nomeq
    AND edad <= 25
) AND EXISTS (
    SELECT * 
    FROM ciclista
    WHERE nomeq = equipo.nomeq
) ORDER BY nomeq;

-- Exercise 26
SELECT dorsal, nombre
FROM ciclista
WHERE NOT EXISTS (
    SELECT *
    FROM etapa
    WHERE dorsal = ciclista.dorsal
    AND km <= 170
) AND EXISTS (
    SELECT *
    FROM etapa
    WHERE dorsal = ciclista.dorsal
) ORDER BY dorsal;


-- Exercise 27
SELECT nombre
FROM ciclista
WHERE dorsal IN (
    SELECT dorsal
    FROM etapa
    WHERE NOT EXISTS (
        SELECT *
        FROM puerto
        WHERE netapa = etapa.netapa
        AND dorsal <> ciclista.dorsal
    ) AND EXISTS (
        SELECT *
        FROM puerto
        WHERE netapa = etapa.netapa
    )
);

-- Exercise 28
SELECT nomeq
FROM equipo
WHERE NOT EXISTS (
    SELECT *
    FROM ciclista
    WHERE dorsal NOT IN (
        SELECT dorsal
        FROM llevar
    ) AND dorsal NOT IN (
        SELECT dorsal
        FROM puerto
    ) AND equipo.nomeq = ciclista.nomeq
) AND EXISTS (
    SELECT *
    FROM ciclista
    WHERE equipo.NOMEQ = ciclista.NOMEQ
);

-- Exercise 29
SELECT codigo, color
FROM maillot
WHERE codigo IN (
    SELECT codigo
    FROM llevar
    WHERE dorsal IN (
        SELECT dorsal
        FROM ciclista c
        WHERE NOT EXISTS (
            SELECT *
            FROM ciclista
            WHERE dorsal IN (
                SELECT dorsal
                FROM llevar
                WHERE codigo = maillot.codigo
            ) AND nomeq <> c.nomeq
        )
    )
);

-- Exercise 30
SELECT nomeq
FROM equipo
WHERE NOT EXISTS (
    SELECT *
    FROM ciclista
    WHERE nomeq = equipo.nomeq
    AND dorsal IN (
        SELECT dorsal
        FROM puerto
        WHERE categoria <> '1'
    )
) AND EXISTS (
    SELECT * 
    FROM ciclista
    WHERE nomeq = equipo.nomeq
    AND dorsal IN (
        SELECT dorsal
        FROM puerto
    )
);


-- QUERIES WITH GROUP BY

-- Exercise 31
SELECT netapa, COUNT(nompuerto) num_puertos
FROM etapa JOIN puerto USING (netapa)
GROUP BY netapa
ORDER BY netapa;

-- Exercise 32
SELECT nomeq, COUNT(dorsal) ciclistas
FROM ciclista
GROUP BY nomeq
ORDER BY nomeq;

-- Exercise 33
SELECT nomeq, COUNT(dorsal) ciclistas
FROM equipo NATURAL LEFT JOIN ciclista
GROUP BY nomeq;

-- Exercise 34
SELECT director, nomeq
FROM equipo NATURAL LEFT JOIN ciclista
GROUP BY nomeq, director
HAVING COUNT(dorsal) > 3
AND AVG(edad) <= 30
ORDER BY director;

-- Exercise 35
SELECT DISTINCT nombre, COUNT(netapa)
FROM (ciclista NATURAL JOIN etapa) JOIN equipo ON (equipo.NOMEQ = ciclista.NOMEQ)
WHERE 5 < (
    SELECT COUNT(dorsal)
    FROM ciclista
    WHERE nomeq = equipo.nomeq
) GROUP BY nombre
ORDER BY nombre;

-- Exercise 36
SELECT nomeq, AVG(edad)
FROM ciclista
GROUP BY nomeq
HAVING AVG(edad) >= ALL (
    SELECT AVG(edad)
    FROM ciclista
    GROUP BY nomeq
);

-- Exercise 37
SELECT director
FROM equipo NATURAL JOIN ciclista NATURAL JOIN llevar
GROUP BY director
HAVING COUNT(codigo) >= ALL (
    SELECT COUNT(codigo)
    FROM equipo NATURAL JOIN ciclista NATURAL JOIN llevar
    GROUP BY director
);


-- OTHER QUERIES

-- Exercise 38
SELECT codigo, color
FROM maillot
WHERE codigo IN (
    SELECT codigo
    FROM llevar
    WHERE dorsal NOT IN (
        SELECT dorsal
        FROM etapa
    )
);

-- Exercise 39
SELECT netapa, salida, llegada
FROM etapa
WHERE km > 190
AND 2 <= (
    SELECT COUNT(nompuerto)
    FROM puerto
    WHERE netapa = etapa.netapa
);

-- Exercise 40
SELECT dorsal, nombre
FROM ciclista
WHERE EXISTS (
    SELECT *
    FROM llevar
    WHERE dorsal = 20
    AND codigo NOT IN (
        SELECT codigo
        FROM llevar
        WHERE ciclista.dorsal = dorsal
    )
);

-- Exercise 41
SELECT dorsal, nombre
FROM ciclista
WHERE dorsal IN (
    SELECT dorsal
    FROM llevar
    WHERE codigo IN (
        SELECT codigo
        FROM llevar
        WHERE dorsal = 20
    )
) AND dorsal <> 20
ORDER BY dorsal;

-- Exercise 42
SELECT dorsal, nombre
FROM ciclista
WHERE dorsal NOT IN (
    SELECT dorsal
    FROM llevar
    WHERE codigo IN (
        SELECT codigo
        FROM llevar
        WHERE dorsal = 20
    )
);

-- Exercise 43
-- ciclista que ha ganado todos los maillots que ha ganado el 20
-- ciclista al que no le falta ningun maillot ganado por el 20
SELECT dorsal, nombre
FROM ciclista
WHERE NOT EXISTS (
    SELECT *
    FROM llevar
    WHERE dorsal = 20
    AND codigo NOT IN (
        SELECT codigo
        FROM llevar
        WHERE dorsal = ciclista.dorsal   
    )   
) AND dorsal <> 20;

-- Exercise 44
-- ciclista que solo ha ganado los maillots que el 20 ha ganado
-- ciclista que ha ganado todos los tipos de maillot que el 20
-- ciclista que no ha ganado ningun maillot que 20 no ha ganado
SELECT dorsal, nombre
FROM ciclista
WHERE NOT EXISTS ( -- he's won all those that 20 has
    SELECT *
    FROM llevar
    WHERE dorsal = 20
    AND codigo NOT IN (
        SELECT codigo
        FROM llevar
        WHERE dorsal = ciclista.dorsal
    )
) AND dorsal <> 20
AND NOT EXISTS ( -- he hasn't won any that 20 hasn't
    SELECT *
    FROM llevar
    WHERE dorsal = ciclista.dorsal
    AND codigo NOT IN (
        SELECT codigo
        FROM llevar
        WHERE dorsal = 20
    )
);

-- Exercise 45
-- ciclista que ha ganado un maillot en etapas con SUM(km) > ANY other
SELECT ciclista.dorsal, nombre, color
FROM ciclista, llevar, etapa, maillot
WHERE etapa.netapa = llevar.netapa
AND ciclista.dorsal = llevar.dorsal
AND llevar.codigo = maillot.codigo
GROUP BY ciclista.dorsal, nombre, color
HAVING SUM(km) >= ALL (
    SELECT SUM(km)
    FROM ciclista, llevar, etapa, maillot
    WHERE etapa.netapa = llevar.netapa
    AND llevar.codigo = maillot.codigo
    AND ciclista.dorsal = llevar.dorsal
    GROUP BY ciclista.dorsal, nombre, color
);

-- Exercise 46
SELECT dorsal, nombre
FROM ciclista NATURAL JOIN llevar
GROUP BY dorsal, nombre
HAVING COUNT(DISTINCT codigo) + 3 = (
    SELECT COUNT(DISTINCT codigo)
    FROM llevar
    WHERE dorsal = 1
) ORDER BY nombre;

SELECT *
FROM maillot;

-- Exercise 47
SELECT DISTINCT netapa, km
FROM etapa JOIN puerto USING (netapa)
ORDER BY netapa;