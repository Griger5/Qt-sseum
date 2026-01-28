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

INSERT INTO item_names (name_id, base_name, prefix, suffix, taken)
SELECT
    gen_random_uuid(),
    i.name,
    pre.prefix,
    suf.suffix,
    false
FROM abstract_item i
CROSS JOIN item_prefix pre
CROSS JOIN item_suffix suf
ON CONFLICT (base_name, prefix, suffix) DO NOTHING;