CREATE TABLE users (
    id uuid PRIMARY KEY NOT NULL,
    username text NOT NULL,
    email text NOT NULL,
    password_hash bytea NOT NULL
);