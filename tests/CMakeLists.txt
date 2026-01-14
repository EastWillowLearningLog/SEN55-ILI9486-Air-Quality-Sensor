# Enable testing
enable_testing()

# Add GoogleTest
# Since external/googletest is in the project root, we refer to it using CMAKE_SOURCE_DIR
add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest ${CMAKE_BINARY_DIR}/googletest)

# Locate GTest
include(GoogleTest)

# Define Test Executable
add_executable(UnitTests
    hello_test.cpp
)

# Link against CoreLib and GTest
target_link_libraries(UnitTests
    PRIVATE
    CoreLib
    gtest
    gtest_main
    gmock
)

# Discover tests
gtest_discover_tests(UnitTests)
