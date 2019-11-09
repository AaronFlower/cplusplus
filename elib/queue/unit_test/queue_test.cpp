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

TEST_F(QueueTest, DefaultConstructor) {
    EXPECT_EQ(0, q0_.size());
}

} // namespace testing
} // namespace elib
