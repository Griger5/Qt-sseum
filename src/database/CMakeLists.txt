add_library(database_dao
    dao/postgres/pg_user_dao.cpp
)

target_link_libraries(database_dao PRIVATE
    utils
    pqxx
)

target_include_directories(database_dao PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)