add_library(database
    dao/postgres/pg_user_dao.cpp
)

target_link_libraries(database PRIVATE
    pqxx
)

target_include_directories(database PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)