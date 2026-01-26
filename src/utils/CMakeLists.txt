add_library(utils
    load_dotenv.cpp
    db_config.cpp
    verify_jwt.cpp
    verify_auth.cpp
)

target_link_libraries(utils PRIVATE
    jwt-cpp
)

target_include_directories(utils PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)