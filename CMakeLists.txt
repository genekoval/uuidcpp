cmake_minimum_required(VERSION 3.26)

include(cmake/modules.cmake)
include(GitVersion)

project(uuidcpp
    VERSION ${GIT_VERSION_ABBREV}
    DESCRIPTION "C++ wrapper for libuuid"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

include(ProjectTesting)
include(packages.cmake)

add_library(uuid++ "")
add_library(${PROJECT_NAME}::uuid++ ALIAS uuid++)

target_sources(uuid++ PUBLIC FILE_SET HEADERS BASE_DIRS include)
target_include_directories(uuid++ PRIVATE ${UUID_INCLUDE_DIRS})

target_link_libraries(uuid++
    PRIVATE
        fmt::fmt
        ${UUID_LIBRARIES}
)

if(PROJECT_TESTING)
    add_executable(uuid++.test "")

    target_link_libraries(uuid++.test
        PRIVATE
            GTest::gtest_main
            uuid++
    )

    add_test("Unit Tests" uuid++.test)
endif()

add_subdirectory(include)
add_subdirectory(src)

include(Sanitizers)
enable_asan()

include(EasyInstall)
easy_install(TARGETS uuid++)

if(PROJECT_IS_TOP_LEVEL)
    add_custom_target(docker
        docker build --progress=plain --no-cache .
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        USES_TERMINAL
    )
endif()
