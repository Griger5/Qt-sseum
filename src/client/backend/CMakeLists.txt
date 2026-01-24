add_library(client_backend
    greeter/greeter_client.cpp
    registration/registration_client.cpp
    auth/auth_client.cpp
)

target_link_libraries(client_backend PUBLIC
    protolib
)

target_include_directories(client_backend PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)