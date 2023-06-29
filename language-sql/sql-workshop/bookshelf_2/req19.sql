CREATE FUNCTION add_book(title VARCHAR(64),
                        author VARCHAR(64),
                        genre VARCHAR(64),
                        release_date DATE)
    RETURNS BOOLEAN AS
$$
BEGIN
    INSERT INTO books
    VALUES (title, author, genre, release_date);

    RETURN TRUE;
END;
$$ LANGUAGE plpgsql;

SELECT add_book('OKOKOK', 'Agatha Christie', 'GODTIER', '2020-10-10'::date)
