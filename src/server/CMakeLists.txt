add_executable(server
    main.cpp
    greeter/greeter_service.cpp
    registration/registration_service.cpp
)

target_link_libraries(server PRIVATE
    protolib
    database_dao
    bcrypt
    utils
)

target_include_directories(server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${bcrypt_SOURCE_DIR}/include
)