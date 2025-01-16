cmake_minimum_required(VERSION 3.16)

project(ESPN_Cricket VERSION 0.1 LANGUAGES CXX)

# Enable automatic features
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required Qt modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets UiTools Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets UiTools Network)

# Define the project sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    tournamentscreen.h
    tournamentscreen.cpp
    tournamentscreen.ui
    championtrophy.h
    championtrophy.cpp
    championtrophy.ui
)

# Add executable or library based on Qt version and platform
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ESPN_Cricket
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ESPN_Cricket SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ESPN_Cricket
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link the required Qt libraries
target_link_libraries(ESPN_Cricket PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::UiTools
    Qt${QT_VERSION_MAJOR}::Network
)

# Set bundle and executable properties
set_target_properties(ESPN_Cricket PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install targets
install(TARGETS ESPN_Cricket
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ESPN_Cricket)
endif()
