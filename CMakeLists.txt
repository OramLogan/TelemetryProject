cmake_minimum_required(VERSION 3.16)

project(telemetry
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library target
add_library(telemetry_lib
    src/TelemetryMessage.cpp
    src/InMemoryTelemetryStore.cpp
    src/TelemetryDatabaseStore.cpp
    src/TelemetryAnalyzer.cpp
    src/TelemetryQueue.cpp
    src/TelemetryProducer.cpp
    src/TelemetryProcessor.cpp
    src/TelemetryPipeline.cpp
    src/TelemetryLogger.cpp
    src/TelemetryReportGenerator.cpp
    src/TelemetryRoutes.cpp
)

target_include_directories(telemetry_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Warnings
target_compile_options(telemetry_lib
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)


# Executable target
add_executable(telemetry_app
    src/main.cpp
)

target_link_libraries(telemetry_app
    PRIVATE telemetry_lib
)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.3.2
)

FetchContent_MakeAvailable(Crow)


#crow
target_link_libraries(telemetry_app PRIVATE Crow::Crow)
target_link_libraries(telemetry_lib PRIVATE Crow::Crow)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

target_include_directories(telemetry_lib PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(telemetry_lib PRIVATE ${PQXX_LIBRARIES})

enable_testing()

add_executable(telemetry_tests
    tests/TelemetryAnalyzerTest.cpp
    tests/TelemetryStoreTest.cpp
    tests/TelemetryMessageTest.cpp
    tests/TelemetryQueueTest.cpp
)

target_link_libraries(telemetry_tests
    PRIVATE
        telemetry_lib
        gtest_main
)

add_test(NAME telemetry_tests COMMAND telemetry_tests)


# Sanitizers (Debug only)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    foreach(target telemetry_lib telemetry_app telemetry_tests)
        target_compile_options(${target}
            PRIVATE
                -fsanitize=address
                -fno-omit-frame-pointer
        )

        target_link_options(${target}
            PRIVATE
                -fsanitize=address
        )
    endforeach()
endif()