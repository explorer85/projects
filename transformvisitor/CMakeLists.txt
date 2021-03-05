cmake_minimum_required(VERSION 3.5)

project(transformvisitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( project_sources
    geopoint.cpp
    geotransform.cpp
    main.cpp
    point.cpp
    transform.cpp)


add_executable(${PROJECT_NAME} ${project_sources})
