cmake_minimum_required(VERSION 3.21)
project(Qt-sseum LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

include(FetchContent)

FetchContent_Declare(
    jwt-cpp
    GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
    GIT_TAG v0.7.1
)
FetchContent_MakeAvailable(jwt-cpp)

FetchContent_Declare(
    bcrypt
    GIT_REPOSITORY https://github.com/trusch/libbcrypt.git
)
FetchContent_MakeAvailable(bcrypt)

set(PROTO_DIR src/proto)

add_library(protolib
    ${PROTO_DIR}/greeter.proto
    ${PROTO_DIR}/registration.proto
)

target_link_libraries(protolib PUBLIC
    gRPC::grpc++
)

target_include_directories(protolib PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/src
)

get_target_property(GRPC_CPP_PLUGIN gRPC::grpc_cpp_plugin LOCATION)

protobuf_generate(TARGET protolib LANGUAGE cpp)

protobuf_generate(TARGET protolib LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${GRPC_CPP_PLUGIN}"
)

add_subdirectory(src/utils)
add_subdirectory(src/database)
add_subdirectory(src/server)
add_subdirectory(src/client)