cmake_minimum_required(VERSION 3.10)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(EmulatorTests)
    
    # If standalone, we need to locate dependencies relative to this folder
    # Assuming standard repo layout
    set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
    
    # Add GoogleTest if not already available
    if(NOT TARGET GTest::gtest_main)
        add_subdirectory(${PROJECT_ROOT}/external/googletest ${CMAKE_BINARY_DIR}/googletest)
    endif()
    
    # We rely on DisplayEmulator being built. In a true standalone unit test of logic,
    # we would link libraries. Here we are integration testing the binary.
    # For now, let's assume the user builds the main project first or we address this later.
endif()

# Enable testing
enable_testing()

# Add GoogleTest
# Since external/googletest is in the project root, we refer to it using CMAKE_SOURCE_DIR
# Only add if NOT already added (handling the case where root added it, or we added it above)
if(NOT TARGET GTest::gtest_main)
    add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest ${CMAKE_BINARY_DIR}/googletest)
endif()

# Locate GTest
include(GoogleTest)

# Build the GTest executable
add_executable(emulator_test emulator_test.cpp)

target_compile_definitions(emulator_test PRIVATE
    TEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/reference"
)

# Link GTest
target_link_libraries(emulator_test
    GTest::gtest_main
)

# Register the test
add_test(NAME EmulatorIntegrationTest COMMAND emulator_test)

# Discover tests
gtest_discover_tests(emulator_test)
