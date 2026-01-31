qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(client_core
    token_manager.cpp
    grpc_client_base.cpp
    session_logic.cpp
)

target_link_libraries(client_core PUBLIC
    protolib
    Qt6::Core
)

target_include_directories(client_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)