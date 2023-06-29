CREATE OR REPLACE FUNCTION duration_to_string(duration INT)
    RETURNS VARCHAR(16) AS
$$
BEGIN
    IF duration <= 0 OR duration IS NULL THEN
        RETURN '0:00';
    END IF;

    RETURN substring(CAST((duration / 60) AS VARCHAR) from '^.+') || ':' || lpad(CAST(MOD(duration, 60) AS VARCHAR), 2, '0');
END;
$$ LANGUAGE plpgsql;
