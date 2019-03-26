cmake_minimum_required(VERSION 3.5)


project(t9 VERSION 0.0.1)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})


set_target_properties(${PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)        


# Unit tests
find_package(GTest)
# enable CTest testing
enable_testing()

# Add a testing executable
add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests gtest gtest_main pthread)
gtest_add_tests(TARGET unit_tests)





