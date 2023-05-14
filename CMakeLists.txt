cmake_minimum_required(VERSION 3.16)

project(countdown VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appcountdown
    main.cpp
)

qt_add_qml_module(appcountdown
    URI Countdown
    VERSION 1.0
    RESOURCE_PREFIX /qt/qml
    QML_FILES Main.qml SettingsView.qml SettingsPopup.qml
)

set_target_properties(appcountdown PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appcountdown
    PRIVATE
    Qt6::Quick
    Qt6::Widgets
)

install(TARGETS appcountdown
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
