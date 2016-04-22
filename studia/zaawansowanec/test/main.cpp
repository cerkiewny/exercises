#include "gtest/gtest.h"

// main.cpp
int test_argc;
char** test_argv;

int main(int argc, char ** argv){
  test_argv = argv;
  test_argc = argc;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

