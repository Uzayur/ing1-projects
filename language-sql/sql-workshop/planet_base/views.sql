CREATE OR REPLACE VIEW view_nearest_planet_to_sun AS
    SELECT name AS planet
    FROM planet
    WHERE id_system = 1
    ORDER BY period
    LIMIT 3;

CREATE OR REPLACE VIEW view_nb_satellite_per_planet AS
    SELECT planet.name AS planet, count(satellite.name) AS "number of satellites"
    FROM planet
    LEFT JOIN satellite ON planet.id = id_planet
    WHERE satellite.radius > 500 OR satellite.radius IS NULL
    GROUP BY planet.name
    ORDER BY "number of satellites", planet.name;

CREATE OR REPLACE VIEW view_average_period AS
    SELECT ps.name AS system, COALESCE(ROUND(avg(planet.period), 2), 0) AS "average_period"
    FROM planetary_system ps
    LEFT JOIN planet ON ps.id = id_system
    GROUP BY ps.name
    ORDER BY "average_period", system;

CREATE OR REPLACE VIEW view_biggest_entities AS
    SELECT "type", "system", "name", "radius" FROM (
        SELECT CAST('planet' AS VARCHAR) AS "type", ps.name AS "system", p.name AS "name", p.radius AS "radius"
        FROM planet p, planetary_system ps
        WHERE p.id_system = ps.id
        ORDER BY p.radius DESC) AS TABLE1
    UNION ALL
    SELECT "type", "system", "name", "radius" FROM (
        SELECT CAST('satellite' AS VARCHAR) AS "type", ps.name as "system", s.name AS "name", s.radius AS "radius"
        FROM planet p, satellite s, planetary_system ps
        WHERE ps.id = p.id_system AND s.id_planet = p.id
        ORDER BY s.radius DESC) AS TABLE2
    ORDER BY radius DESC, "name"
    LIMIT 10;
