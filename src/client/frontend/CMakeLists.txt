qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(client
    main.cpp
    grpc_client/grpc_client_qt.cpp
)

target_link_libraries(client PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    client_backend
)

target_include_directories(client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

qt_add_qml_module(client
    URI ClientApp
    QML_FILES qml/Main.qml
)