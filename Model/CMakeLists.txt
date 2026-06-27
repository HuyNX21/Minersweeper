cmake_minimum_required(VERSION 3.16)
project(ModelMine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -O2)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)

file(GLOB MODEL_BLACKAPI_SOURCES
    ${CMAKE_SOURCE_DIR}/BlackAPI/BaseLibrary/*.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Common/*.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/BLKC_MarshalWrapper.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/BLKC_UnmarshalWrapper.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/BLKC_MarshalWrapperStub.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/BLKC_UnmarshalWrapperStub.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/marsahling.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Marshaling/unmarsahling.cpp
	${CMAKE_SOURCE_DIR}/BlackAPI/Server/*.cpp
	${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Connect/*.cpp
	${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Stub/*.cpp
	${CMAKE_SOURCE_DIR}/BlackAPI/Server/Stub/include/*.cpp
	${CMAKE_SOURCE_DIR}/BlackAPI/Server/Stub_Observer/*.cpp
	${CMAKE_SOURCE_DIR}/BlackAPI/Server/Stub/src/*.cpp
	${CMAKE_SOURCE_DIR}/BlackAPI/CoreSrc/*.cpp
    ${CMAKE_SOURCE_DIR}/BlackAPI/PortNumber/server/ServerPortNumber.cpp
)

add_executable(ModelMine
    main.cpp
    MineModel/APIC_MineModel.cpp
    MineModel/MDLC_MineModel.cpp
    MineModel/MineSetting.cpp
    MineModel/HmacUtils.cpp
    MineModel/BestTimesStorage.cpp
    ${MODEL_BLACKAPI_SOURCES}
)

target_precompile_headers(ModelMine PRIVATE
    "${CMAKE_SOURCE_DIR}/BlackAPI/BLK_Common/pch.h"
)

target_include_directories(ModelMine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/MineModel
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

target_link_libraries(ModelMine
    PRIVATE
        Threads::Threads
        OpenSSL::Crypto
        nlohmann_json::nlohmann_json
)
