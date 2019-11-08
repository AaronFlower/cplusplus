#include "todocore/todo.h"

#include <string>
using std::string;

#include <gmock/gmock.h>
using ::testing::Eq;

#include <gtest/gtest.h>
using ::testing::Test;


namespace ToDoCore
{
namespace testing
{
    class ToDoTest: public Test
    {
    protected:
        ToDoTest(){}
        ~ToDoTest(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        ToDo list;

        static const size_t taskCount = 3;
        static const string tasks[taskCount];
    };

    const string ToDoTest::tasks[taskCount] = {"write code",
                                                "compile",
                                                "test"};

    TEST_F(ToDoTest, constructor_createEmptyList)
    {
        EXPECT_THAT(list.size(), Eq(size_t(0)));
    }

    TEST_F(ToDoTest, sizeIsThree)
    {
        list.addTask(tasks[0]);
        list.addTask(tasks[1]);
        list.addTask(tasks[2]);

        EXPECT_THAT(list.size(), Eq(taskCount));
    }


} // namespace testing
} // namespace ToDoCore
