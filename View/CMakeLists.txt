cmake_minimum_required(VERSION 3.16)

project(Minersweeper VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -O2)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Threads REQUIRED)

file(GLOB BLACKAPI_SERVER_SOURCES
    ${CMAKE_SOURCE_DIR}/BlackAPI/BaseLibrary/*.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Common/*.cpp
	${CMAKE_SOURCE_DIR}/BlackAPI/PortNumber/client/ClientPortNumber.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/BLKC_MarshalWrapper.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/BLKC_UnmarshalWrapper.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/BLKC_MarshalWrapperProxy.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/BLKC_UnmarshalWrapperProxy.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/marsahling.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/unmarsahling.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Observable/*.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Observable/ObservableClasses/*.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Proxy/*.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/Client/Proxy/include/*.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/Client/Proxy/src/*.cpp
)

set(PROJECT_SOURCES
        main.cpp

        MineView/BestTimeEntry.h

        MineView/MineView.h
        MineView/MineView.cpp
        MineView/CellButton.h

        MineView/Scr1/BoardSellectModeWidget.h
        MineView/Scr1/BoardSellectModeWidget.cpp
        MineView/Scr1/ButtonsSelectMode.h
        MineView/Scr1/ButtonsSelectMode.cpp
        MineView/Scr1/CustomGameDialog.h
        MineView/Scr1/CustomGameDialog.cpp

        MineView/Scr2/BoardGameContainerWidget.h
        MineView/Scr2/BoardGameContainerWidget.cpp
        MineView/Scr2/MineBoardGame.h
        MineView/Scr2/MineBoardGame.cpp
        MineView/Scr2/SidePanel.h
        MineView/Scr2/SidePanel.cpp
        MineView/Scr2/BestTimesDialog.h
        MineView/Scr2/BestTimesDialog.cpp

        MineController/MineController.h
        MineController/MineController.cpp
        ${BLACKAPI_SERVER_SOURCES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AppMine
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AppMine APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt_add_executable.html#target-creation
else()
    if(ANDROID)
        add_library(AppMine SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AppMine
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(AppMine PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Threads::Threads)

target_precompile_headers(AppMine PRIVATE
    "${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Common/pch.h"
)

target_include_directories(AppMine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/MineView
    ${CMAKE_CURRENT_SOURCE_DIR}/MineView/Scr1
    ${CMAKE_CURRENT_SOURCE_DIR}/MineView/Scr2
    ${CMAKE_CURRENT_SOURCE_DIR}/MineController
    ${CMAKE_SOURCE_DIR}/BlackAPI
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Common
    ${CMAKE_SOURCE_DIR}/BlackAPI/BaseLibrary
    ${CMAKE_SOURCE_DIR}/BlackAPI/PortNumber
    ${CMAKE_SOURCE_DIR}/BlackAPI/PortNumber/server
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Connect
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Stub
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Observable
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Observable/ObservableClasses
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Proxy
    ${CMAKE_SOURCE_DIR}/BlackAPI/Client/Proxy/include
    ${CMAKE_SOURCE_DIR}/BlackAPI/Client/Proxy/src
    ${CMAKE_SOURCE_DIR}/BlackAPI/Server
    ${CMAKE_SOURCE_DIR}/BlackAPI/Server/Stub/include
    ${CMAKE_SOURCE_DIR}/BlackAPI/Server/Stub_Observer
    ${CMAKE_SOURCE_DIR}/BlackAPI/Server/Stub/src
    ${CMAKE_SOURCE_DIR}/BlackAPI/CoreSrc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AppMine)
endif()
set_target_properties(AppMine PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AppMine
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AppMine)
endif()
