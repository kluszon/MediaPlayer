cmake_minimum_required(VERSION 3.14)

project(MediaPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Multimedia)

set(PROJECT_SOURCES
    source/main.cpp
    source/model/medialistmodel.h source/model/medialistmodel.cpp
    source/model/mediafile.h source/model/mediafile.cpp
    source/media/mediamanager.h source/media/mediamanager.cpp
    source/media/mediaplayer.h source/media/mediaplayer.cpp
    source/time/timeutils.h source/time/timeutils.cpp
    qml.qrc
    resources.qrc
    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MediaPlayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET MediaPlayer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MediaPlayer SHARED
            ${PROJECT_SOURCES}
            )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MediaPlayer
            ${PROJECT_SOURCES}
            )
    endif()
endif()

include_directories(library/libtag)
include_directories(source)

add_library(libtag STATIC IMPORTED)

target_link_libraries(MediaPlayer PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${QT_VERSION_MAJOR}::Multimedia
    tag
    )

set_target_properties(MediaPlayer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    )

install(TARGETS MediaPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(MediaPlayer)
    qt_finalize_executable(MediaPlayer)
endif()
