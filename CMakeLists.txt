cmake_minimum_required(VERSION 3.16)

project(countdown VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Widgets LinguistTools)

qt_standard_project_setup(REQUIRES 6.4)

qt_add_executable(appcountdown
    main.cpp applogic.h applogic.cpp
)

qt_add_qml_module(appcountdown
    URI Countdown
    VERSION 1.0
    RESOURCE_PREFIX /qt/qml
    QML_FILES Empty.qml Main.qml SettingsView.qml SettingsPopup.qml
    RESOURCES background.jpg timeoutbackground.jpg logo.png translations_en_US.qm translations_fi_FI.qm
)

qt_add_lupdate(appcountdown TS_FILES translations_en_US.ts translations_fi_FI.ts)
qt_add_lrelease(appcountdown TS_FILES translations_en_US.ts translations_fi_FI.ts
 OPTIONS -idbased)

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
