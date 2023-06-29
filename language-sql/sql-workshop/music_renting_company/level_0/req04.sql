INSERT INTO music
VALUES (1, 'Le Petit Pain au Chocolat', (SELECT id FROM artist WHERE name = 'Joe DASSIN'), 210),
(2, 'Comment lui dire', (SELECT id FROM artist WHERE name = 'France GALL'), 210),
(3, 'C''est ta chance',  (SELECT id FROM artist WHERE name = 'Jean-Jacques GOLDMAN'), 391),
(4, 'Siffler sur la colline', (SELECT id FROM artist WHERE name = 'Joe DASSIN'), 152);
