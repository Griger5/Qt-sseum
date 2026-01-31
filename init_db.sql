CREATE TYPE user_role AS ENUM ('user', 'admin');

CREATE TABLE users (
    id uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    username text NOT NULL,
    email text NOT NULL,
    password_hash text NOT NULL,
    role user_role NOT NULL DEFAULT 'user'
);

CREATE TABLE player_stats (
    id uuid PRIMARY KEY,
    money integer NOT NULL,
    level integer NOT NULL,
    exp integer NOT NULL,
    FOREIGN KEY (id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE abstract_item (
    name text PRIMARY KEY
);

CREATE TABLE item_prefix (
    prefix text PRIMARY KEY,
    strength integer,
    dexterity integer,
    defence integer,
    vitality integer
);

CREATE TABLE item_suffix (
    suffix text PRIMARY KEY,
    strength integer,
    dexterity integer,
    defence integer,
    vitality integer
);

CREATE TABLE item_names (
    name_id uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    base_name text NOT NULL,
    prefix text NOT NULL,
    suffix text NOT NULL,
    taken boolean NOT NULL,
    FOREIGN KEY (base_name) REFERENCES abstract_item(name),
    FOREIGN KEY (prefix) REFERENCES item_prefix(prefix),
    FOREIGN KEY (suffix) REFERENCES item_suffix(suffix)
);

ALTER TABLE item_names
ADD CONSTRAINT unique_item_name
UNIQUE (base_name, prefix, suffix);

CREATE TABLE item_instance (
    item_id uuid PRIMARY KEY,
    name_id uuid NOT NULL,
    min_damage integer NOT NULL,
    max_damage integer NOT NULL,
    FOREIGN KEY (name_id) REFERENCES item_names(name_id)
);

CREATE TYPE gladiator_class AS ENUM ('Gallius', 'Dimachaerus', 'Hoplomachus', 'Retiarius', 'Murmillo');

CREATE TABLE gladiators (
    gladiator_id uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    owner_id uuid NOT NULL,
    name text NOT NULL,
    class gladiator_class NOT NULL,
    strength integer NOT NULL,
    dexterity integer NOT NULL,
    defence integer NOT NULL,
    vitality integer NOT NULL,
    item_id uuid,
    FOREIGN KEY (owner_id) REFERENCES users(id),
    FOREIGN KEY (item_id) REFERENCES item_instance(item_id)
);

CREATE TABLE fights (
    fight_id uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    player1_id uuid NOT NULL,
    player2_id uuid,
    gladiator1_id uuid NOT NULL,
    gladiator2_id uuid,
    result boolean NOT NULL,
    FOREIGN KEY (player1_id) REFERENCES users(id),
    FOREIGN KEY (player2_id) REFERENCES users(id),
    FOREIGN KEY (gladiator1_id) REFERENCES gladiators(gladiator_id),
    FOREIGN KEY (gladiator2_id) REFERENCES gladiators(gladiator_id)
);

CREATE TYPE special_move AS ENUM ('critical', 'block');

CREATE TABLE fight_turns (
    fight_id uuid NOT NULL,
    turn_idx integer NOT NULL,
    who_attacks boolean NOT NULL,
    special_action special_move,
    damage integer,
    PRIMARY KEY (fight_id, turn_idx),
    FOREIGN KEY (fight_id) REFERENCES fights(fight_id) ON DELETE CASCADE
);

CREATE TABLE market (
    offer_id uuid PRIMARY KEY,
    item_id uuid NOT NULL,
    player_id uuid NOT NULL,
    price integer NOT NULL,
    FOREIGN KEY (item_id) REFERENCES item_instance(item_id),
    FOREIGN KEY (player_id) REFERENCES users(id)
);

CREATE OR REPLACE FUNCTION create_player_stats()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO player_stats(id, money, level, exp)
    VALUES (NEW.id, 100, 1, 0);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION generate_item_name_combinations()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO item_names (name_id, base_name, prefix, suffix, taken)
    SELECT
        gen_random_uuid(),
        ai.name,
        ip.prefix,
        isf.suffix,
        false
    FROM abstract_item ai
    CROSS JOIN item_prefix ip
    CROSS JOIN item_suffix isf
    ON CONFLICT (base_name, prefix, suffix) DO NOTHING;

    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_generate_item_names_on_base
AFTER INSERT ON abstract_item
FOR EACH STATEMENT
EXECUTE FUNCTION generate_item_name_combinations();

CREATE TRIGGER trigger_generate_item_names_on_prefix
AFTER INSERT ON item_prefix
FOR EACH STATEMENT
EXECUTE FUNCTION generate_item_name_combinations();

CREATE TRIGGER trigger_generate_item_names_on_suffix
AFTER INSERT ON item_suffix
FOR EACH STATEMENT
EXECUTE FUNCTION generate_item_name_combinations();

CREATE TRIGGER trigger_create_player_stats
AFTER INSERT ON users
FOR EACH ROW
EXECUTE FUNCTION create_player_stats();

CREATE OR REPLACE FUNCTION create_starting_gladiator()
RETURNS TRIGGER AS $$
DECLARE
    name_pool text[] := ARRAY[
        'Aurelius',
        'Maximus',
        'Cassius',
        'Brutus',
        'Tiberius',
        'Valerius',
        'Octavian',
        'Lucanus'
    ];
    chosen_name text;
    chosen_class gladiator_class;
BEGIN
    chosen_name := name_pool[1 + floor(random() * array_length(name_pool, 1))::int];

    SELECT val
    INTO chosen_class
    FROM unnest(enum_range(NULL::gladiator_class)) AS val
    ORDER BY random()
    LIMIT 1;

    INSERT INTO gladiators (owner_id, name, class, strength, dexterity, defence, vitality, item_id)
    VALUES (NEW.id, chosen_name, chosen_class, 5, 5, 5, 5, NULL);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_create_starting_gladiator
AFTER INSERT ON users
FOR EACH ROW
EXECUTE FUNCTION create_starting_gladiator();

CREATE OR REPLACE FUNCTION update_player_level()
RETURNS TRIGGER AS $$
BEGIN
    NEW.level := FLOOR(NEW.exp / 100)::integer + 1;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_player_level
BEFORE UPDATE ON player_stats
FOR EACH ROW
WHEN (OLD.exp IS DISTINCT FROM NEW.exp)
EXECUTE FUNCTION update_player_level();

CREATE OR REPLACE FUNCTION create_item_instance_for_new_name()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO item_instance (item_id, name_id, min_damage, max_damage)
    VALUES (
        gen_random_uuid(),
        NEW.name_id,
        (floor(random() * 10)::int + 1),
        (floor(random() * 10)::int + 11)
    );
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_create_item_instance
AFTER INSERT ON item_names
FOR EACH ROW
EXECUTE FUNCTION create_item_instance_for_new_name();

CREATE OR REPLACE FUNCTION assign_random_weapon_to_gladiator()
RETURNS TRIGGER AS $$
DECLARE
    chosen_item_id uuid;
BEGIN
    SELECT ii.item_id
    INTO chosen_item_id
    FROM item_instance ii
    JOIN item_names iname ON iname.name_id = ii.name_id
    WHERE iname.taken = false
    ORDER BY random()
    LIMIT 1;

    IF chosen_item_id IS NOT NULL THEN
        UPDATE gladiators
        SET item_id = chosen_item_id
        WHERE gladiator_id = NEW.gladiator_id;

        UPDATE item_names
        SET taken = true
        WHERE name_id = (SELECT name_id FROM item_instance WHERE item_id = chosen_item_id);
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_assign_random_weapon
AFTER INSERT ON gladiators
FOR EACH ROW
EXECUTE FUNCTION assign_random_weapon_to_gladiator();