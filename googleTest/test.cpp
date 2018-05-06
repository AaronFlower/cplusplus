#include <iostream>
#include <gtest/gtest.h>

using std::cout;
using std::endl;

int sum(int a, int b) {
    return a + b;
}


TEST(AddTest, PositiveNumbers) {
    EXPECT_EQ(2, sum(1, 1));
    EXPECT_EQ(1024, sum(1000, 24));
}

TEST(AddTest, NegativeNumbers) {
    EXPECT_EQ(0, sum(-1, 1));
    EXPECT_EQ(23, sum(-1, 24));
    EXPECT_EQ(-23, sum(-1, 24));
}


int main(int argc, char **argv) {
    cout << "Hello Google Test " << endl;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
