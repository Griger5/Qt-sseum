CREATE TYPE user_role AS ENUM ('user', 'admin');

CREATE TABLE users (
    id uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    username text NOT NULL,
    email text NOT NULL,
    password_hash text NOT NULL,
    role user_role NOT NULL DEFAULT 'user'
);