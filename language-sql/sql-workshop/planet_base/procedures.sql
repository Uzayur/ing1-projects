CREATE OR REPLACE FUNCTION space_travel(origin INT, destination INT, quantity BIGINT)
    RETURNS boolean AS
$$
DECLARE
    pop_begin BIGINT;
    sys_begin INT;
    sys_dest INT;

BEGIN
    SELECT population INTO pop_begin
    FROM planet
    WHERE id = origin;

    SELECT id_system INTO sys_begin
    FROM planet
    WHERE id = origin;

    SELECT id_system INTO sys_dest
    FROM planet
    WHERE id = destination;

    IF quantity <= 0 OR sys_dest != sys_begin THEN
        RETURN FALSE;
    ELSIF pop_begin < quantity THEN
        RETURN FALSE;
    END IF;

    UPDATE planet
    SET population = population - quantity
    WHERE id = origin;

    UPDATE planet
    SET population = population + quantity
    WHERE id = destination;

    RETURN TRUE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION list_satellite_inf_750(syst INT)
    RETURNS TABLE(satellite VARCHAR(32), planet VARCHAR(32), radius INT) AS
$$
BEGIN
    RETURN QUERY
    SELECT DISTINCT s.name AS satellite, p.name AS planet, s.radius
    FROM planet p, satellite s, planetary_system ps
    WHERE s.radius <= 750
    AND s.id_planet = p.id
    AND p.id_system = syst
    ORDER BY planet, s.radius DESC, s.name;
END;
$$ LANGUAGE plpgsql;
