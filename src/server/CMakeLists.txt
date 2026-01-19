add_executable(server
    main.cpp
    greeter/greeter_service.cpp
)

target_link_libraries(server PRIVATE
    protolib
)

target_include_directories(server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)