cmake_minimum_required(VERSION 3.16)

project(RockPaperScissors VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appRockPaperScissors
    main.cpp
)

qt_add_qml_module(appRockPaperScissors
    URI RockPaperScissors
    VERSION 1.0
    QML_FILES
    MainMenu.qml
    QML_FILES CreateRoom.qml
    SOURCES
    QML_FILES JoinRoom.qml
    QML_FILES Game.qml
    QML_FILES Main.qml
    SOURCES NetworkManager.h NetworkManager.cpp
    QML_FILES CustomButton.qml
    RESOURCES resources.qrc
    QML_FILES PulsingCircle.qml
    QML_FILES LoadingDots.qml
    QML_FILES CustomTextField.qml
    QML_FILES CustomText.qml
    SOURCES GameServer.h GameServer.cpp
    SOURCES GameClient.h GameClient.cpp
    SOURCES GameLogic.h GameLogic.cpp
    SOURCES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appRockPaperScissors PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appRockPaperScissors
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appRockPaperScissors
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appRockPaperScissors
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
