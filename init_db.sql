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

CREATE TABLE item_instance (
    item_id uuid PRIMARY KEY,
    name_id uuid NOT NULL,
    min_damage integer NOT NULL,
    max_damage integer NOT NULL,
    FOREIGN KEY (name_id) REFERENCES item_names(name_id)
);


CREATE TABLE gladiators (
    gladiator_id uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    owner_id uuid NOT NULL,
    name text NOT NULL,
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