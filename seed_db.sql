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

INSERT INTO item_prefix (prefix, strength, dexterity, defence, vitality) VALUES
  ('Gaius', 3, 0, 0, 0),
  ('Ceaser', 1, 2, 2, 1),
  ('Servius', 4, -1, 1, 0)
ON CONFLICT DO NOTHING;

INSERT INTO item_suffix (suffix, strength, dexterity, defence, vitality) VALUES
  ('of Accuracy', 0, 3, 0, 0),
  ('of Power', 3, 1, -1, -1),
  ('of Blood', 0, 0, 2, 2)
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