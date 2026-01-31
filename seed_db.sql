INSERT INTO abstract_item (name) VALUES
    ('Longsword'),
    ('Axe'),
    ('Dagger'),
    ('Mace'),
    ('Spear'),
    ('Trident'),
    ('Hammer'),
    ('Gladius')
ON CONFLICT DO NOTHING;

INSERT INTO item_prefix (prefix, strength, dexterity, defence, vitality)
SELECT
    name,
    (floor(random() * 6))::int,
    (floor(random() * 6))::int,
    (floor(random() * 6))::int,
    (floor(random() * 6))::int
FROM (VALUES
    ('Gaius'),
    ('Ceaser'),
    ('Servius')
) AS temp(name)
ON CONFLICT DO NOTHING;

INSERT INTO item_suffix (suffix, strength, dexterity, defence, vitality)
SELECT
    name,
    (floor(random() * 6))::int,
    (floor(random() * 6))::int,
    (floor(random() * 6))::int,
    (floor(random() * 6))::int
FROM (VALUES
    ('of Accuracy'),
    ('of Power'),
    ('of Blood')
) AS temp(name)
ON CONFLICT DO NOTHING;

INSERT INTO users (username, email, password_hash) VALUES
    ('Krecimierz', 'kret@kretowisko.pl', '$2a$12$r3dFZ.QDg.N.O7Q7iz6tLO4njfsdRhXJNCEm1WNSyAp6hGyxn7o2e'),
    ('Cezar', 'juliusz@rzym.it', '$2a$12$tAw8qXzYlcU2gKx.0/HSAePP1zXBzUCasw.yAADuFM1MlVh9A8liO'),
    ('Maksimus', 'maks@gmail.com', '$2a$12$f7OC6p0QrCr3BM2U4.YLp.n226r1XTLUoLGw8.z5snYqUI53JKkGy'),
    ('Spartakus', 'spartakus@gmail.com', '$2a$12$Q2MEMA9Uj5bfnF./2vFFW.VPqyrj3pg61Tl2S2/WcV/YIAGBc1iWG'),
    ('Destruktor', 'destruktor@gmail.com', '$2a$12$X6YOkR9xSup1ILoo09QQFeWGXfiS5ZVZKx9niUpdKD6AZ.eaP4qIG')