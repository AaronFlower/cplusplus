#include "gtest/gtest.h"
using ::testing::Test;

#include "queue/queue.h"

namespace elib
{
namespace testing
{

class QueueTest: public Test {
    protected:
        QueueTest(){}
        ~QueueTest(){}

        virtual void SetUp() {}
        virtual void TearDown() {}
    Queue<int> q0_;
};

// Tests the default c'tor
TEST_F(QueueTest, DefaultConstructor) {
    EXPECT_EQ(0, q0_.size());
}

// Tests Pop
TEST_F(QueueTest, Pop) {
    q0_.pop();
    EXPECT_TRUE(q0_.size() == 0);

    q0_.push(1);
    q0_.push(2);
    q0_.push(3);
    q0_.push(4);
    EXPECT_EQ(q0_.size(), 4);
}

} // namespace testing
} // namespace elib
