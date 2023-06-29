CREATE OR REPLACE VIEW view_artists AS
    SELECT name AS artist, birth_date as birthdate, count(music.title) AS songs
    FROM artist
    LEFT OUTER JOIN music ON artist.id = art_id
    GROUP BY artist, birthdate
    ORDER BY artist;

CREATE OR REPLACE VIEW view_albums AS
    SELECT album.name AS album, count(music.title) AS songs,
    duration_to_string(COALESCE(duration, 0)) AS duration
    FROM album
    LEFT OUTER JOIN music_album ON album.id = music_album.alb_id
    LEFT OUTER JOIN music ON music.id = music_album.music_id
    GROUP BY album.name, duration
    ORDER BY album.name;

CREATE OR REPLACE VIEW view_songs AS
    SELECT m.title AS music, artist.name AS artist, duration_to_string(m.duration) AS duration
    FROM music m
    LEFT OUTER JOIN artist ON artist.id = art_id
    ORDER BY music, artist;
