add_library(client_backend
    greeter/greeter_client.cpp
    registration/registration_client.cpp
    auth/auth_client.cpp
    user/user_client.cpp
    trainer/trainer_client.cpp
    arena/arena_client.cpp
)

target_link_libraries(client_backend PUBLIC
    protolib
    client_core
)

target_include_directories(client_backend PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)