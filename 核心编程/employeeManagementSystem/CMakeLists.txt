cmake_minimum_required(VERSION 3.29)
project(employeeManagementSystem)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(employeeManagementSystem
        include/workerManager.h
        src/workerManager.cpp
        main.cpp
        include/worker.h
        include/employee.h
        src/employee.cpp
        include/manager.h
        src/manager.cpp
        include/boss.h
        src/boss.cpp)
