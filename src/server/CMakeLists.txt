add_executable(server
    main.cpp
    greeter/greeter_service.cpp
    registration/registration_service.cpp
    auth/auth_service.cpp
    user/user_service.cpp
    trainer/trainer_service.cpp
    arena/arena_service.cpp
)

target_link_libraries(server PRIVATE
    protolib
    database_dao
    bcrypt
    jwt-cpp
    uuid_v4::uuid_v4
    utils
    gRPC::grpc++
    protobuf::libprotobuf
    ssl
    crypto
    z
    pthread
)

target_include_directories(server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${bcrypt_SOURCE_DIR}/include
)