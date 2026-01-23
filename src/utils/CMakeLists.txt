add_library(utils
    load_dotenv.cpp
    db_config.cpp
)

target_include_directories(utils PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)