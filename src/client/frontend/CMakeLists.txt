qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(client
    main.cpp
    greeter/greeter_client_qt.cpp
    greeter/greeter_worker.cpp
    registration/registration_client_qt.cpp
    registration/registration_worker.cpp
    auth/auth_client_qt.cpp
    auth/auth_worker.cpp
)

target_link_libraries(client PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    client_core
    client_backend
    utils
)

target_include_directories(client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

qt_add_qml_module(client
    URI ClientApp
    QML_FILES 
        qml/Main.qml 
        qml/Navigator.qml
        qml/LoginPage.qml
        qml/RegisterPage.qml
        qml/GreeterPage.qml
)