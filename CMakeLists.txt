cmake_minimum_required(VERSION 3.10)

project(PasswordManager VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    src/password.cpp
    src/manager.cpp
    src/passwordBA.cpp
    src/passwordCM.cpp)

add_executable(PasswordManager ${SOURCES})

target_include_directories(PasswordManager PUBLIC "${PROJECT_SOURCE_DIR}/include")