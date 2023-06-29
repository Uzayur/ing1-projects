CREATE TABLE trigger_change (
    id SERIAL   PRIMARY KEY,
    date TIMESTAMP NOT NULL,
    "old population" BIGINT NOT NULL,
    "new population" BIGINT NOT NULL
);

CREATE OR REPLACE VIEW view_earth_population_evolution AS
    SELECT id, to_char(date, 'DD/MM/YYYY HH24:MI:SS') AS date, "old population", "new population" FROM trigger_change;

CREATE OR REPLACE FUNCTION trigger_trigger()
RETURNS TRIGGER AS
$$
BEGIN
    IF OLD.name = 'Earth' THEN
    INSERT INTO trigger_change
    VALUES(DEFAULT, now(), OLD.population, NEW.population);
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER store_earth_population_updates BEFORE UPDATE ON planet
    FOR EACH ROW
    WHEN (OLD.population IS DISTINCT FROM NEW.population)
    EXECUTE PROCEDURE trigger_trigger();
