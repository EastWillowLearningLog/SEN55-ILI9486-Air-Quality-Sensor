#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Helper to execute command and return exit code
int RunCommand(const char *cmd) { return system(cmd); }

// Helper to read BMP file into buffer
std::vector<char> ReadFile(const char *filename) {
  std::ifstream file(filename, std::ios::binary);
  std::vector<char> buffer((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
  return buffer;
}

class EmulatorTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Clean up previous artifacts
    remove("screenshot.bmp");
  }

  void TearDown() override {
    // Optional cleanup
  }

  std::string GetReferencePath(const std::string &filename) {
#ifdef TEST_RESOURCE_DIR
    return std::string(TEST_RESOURCE_DIR) + "/" + filename;
#else
    return "tests/reference/" + filename;
#endif
  }
};

TEST_F(EmulatorTest, RunsInTestModeAndProducesOutput) {
  // Run emulator in test mode
  int result = RunCommand("../DisplayEmulator --test");
  EXPECT_EQ(result, 0)
      << "Emulator failed to execute or returned non-zero exit code";

  // Verify screenshot exists
  std::ifstream screenshot("screenshot.bmp");
  EXPECT_TRUE(screenshot.good()) << "screenshot.bmp was not created";
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
