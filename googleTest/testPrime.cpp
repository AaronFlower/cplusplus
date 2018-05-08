#include "gtest/gtest.h"
#include "math.h"

// Tests negative input.
TEST(isPrimeTest, Negative) {
  // This test belongs to the isPrimeTest test case.

  EXPECT_FALSE(isPrime(-1));
  EXPECT_FALSE(isPrime(-2));
  EXPECT_FALSE(isPrime(INT_MIN));
}

// Tests some trivial cases.
TEST(isPrimeTest, Trivial) {
  EXPECT_FALSE(isPrime(0));
  EXPECT_FALSE(isPrime(1));
  EXPECT_TRUE(isPrime(2));
  EXPECT_TRUE(isPrime(3));
}

// Tests positive input.
TEST(isPrimeTest, Positive) {
  EXPECT_FALSE(isPrime(4));
  EXPECT_TRUE(isPrime(5));
  EXPECT_FALSE(isPrime(6));
  EXPECT_TRUE(isPrime(23));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



