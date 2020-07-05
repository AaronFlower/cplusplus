//
// Created by eason on 2020/7/5.
//
#include <gtest/gtest.h>
#include "move_checker.h"

TEST(MOVE_CHECKER, begin) {
    move_checker checker;

    EXPECT_EQ(checker.copies(), 0);
    EXPECT_EQ(checker.moves(), 0);

    move_checker copy(checker);
    EXPECT_EQ(copy.copies(), 1);
    EXPECT_EQ(copy.moves(), 0);

    move_checker moved(std::move(checker));
    EXPECT_EQ(moved.copies(), 1);
    EXPECT_EQ(moved.moves(), 1);
}

