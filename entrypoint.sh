#!/bin/sh

cd /workspace

cmake -S . -B build
cmake --build build

until pg_isready -h "${DB_HOST:-db}" -p "${DB_PORT:-5432}"; do
    echo "Waiting for PostgreSQL..."
    sleep 1
done

./build/src/server/server