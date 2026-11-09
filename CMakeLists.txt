cmake_minimum_required(VERSION 3.16)

project(cpp_filecheck VERSION 1.0.0 DESCRIPTION "C++ file-checking CLI demonstrating Jenkins CI/CD" LANGUAGES CXX)

include(GNUInstallDirs)
include(CTest)

option(FILECHECK_BUILD_TESTS "Build unit tests" ${BUILD_TESTING})
option(FILECHECK_ENABLE_WARNINGS "Enable compiler warnings" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(filecheck_lib src/checker.cpp)
target_include_directories(filecheck_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(FILECHECK_ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(filecheck_lib PRIVATE /W4 /permissive-)
    else()
        target_compile_options(filecheck_lib PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
    endif()
endif()

add_executable(filecheck src/main.cpp)
target_link_libraries(filecheck PRIVATE filecheck_lib)

if(FILECHECK_BUILD_TESTS)
    add_subdirectory(tests)
endif()

install(TARGETS filecheck RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(CPACK_PACKAGE_NAME "cpp-filecheck")
set(CPACK_PACKAGE_VENDOR "cpp-jenkins-cicd-demo")
set(CPACK_PACKAGE_CONTACT "maintainers@example.invalid")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A C++ file-checking CLI demo")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "TGZ;ZIP")
include(CPack)

