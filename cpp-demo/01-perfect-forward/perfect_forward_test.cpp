//
// Created by eason on 2020/7/5.
//
#include <gtest/gtest.h>
#include "move_checker.h"
#include <future>

// print the content of an iterable
template <typename Iterable>
void printContents(const Iterable & iterable) {
    std::cout << "print: " << std::this_thread::get_id() << std::endl;
    for (auto e:iterable) {
        std::cout << e << std::endl;
    }
}


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

TEST(MOVE_CHECKER, async_origin) {
    move_checker checker;

    EXPECT_EQ(checker.copies(), 0);
    EXPECT_EQ(checker.moves(), 0);

    std::cout << "test main: " << std::this_thread::get_id() << std::endl;

    std::future<void> task = std::async(
            std::launch::async,
            printContents<move_checker>,
                    checker // lvalue
            );

    task.wait();
    // To ensure users don't shoot themselves,  the async function
    // preemptively copies an lvalue argument in the event that the lvalue
    // goes out of scope, and is destroyed before the thread completes its
    // function.
    // 调用 async 函数开启一个新的线程，但是如果线程还没有执行完，传入的 lvalue
    // 参数就被释放了，那岂不是要 core 。所以 async 会武断地对 lvalue 进行一个拷贝
    // 然后再将 copy 后的参数，move 到线程中，所以下面的值就可以解释得通了。
    // 1) std::async 函数会对参数进行 copy.
    // 2) copy 后的值会被 move 到线程中。
    EXPECT_EQ(checker.copies(), 1);
    EXPECT_EQ(checker.moves(), 1);
}

TEST(MOVE_CHECKER, async_move) {
    move_checker checker;

    EXPECT_EQ(checker.copies(), 0);
    EXPECT_EQ(checker.moves(), 0);

    std::cout << "test main: " << std::this_thread::get_id() << std::endl;

    std::future<void> task = std::async(
            std::launch::async,
            printContents<move_checker>,
                    std::move(checker) // rvalue
            );

    task.wait();
    // 1) 调用 std::move 后，参数成了 rvalue 就不用拷贝了。然后 async 再把参数 move 到线程中。
    // 所以会出现两次 move.
    EXPECT_EQ(checker.copies(), 0);
    EXPECT_EQ(checker.moves(), 2);
}

// 上面两种是调用 `std::async` 安全的方式，对于一般用户足够用了。但是如果我们要
// 实现一个库的话，我们可能需要避免 copy，那么我们需要传入一个指针或才使用 `std::ref` 来
// 包裹一个引用才行。
//
// 需要注意的是 `std::ref` 只对 `lvalue` 有效，对于 `rvalue` 我们不能使用 `std::ref`.

TEST(MOVE_CHECKER, async_ref) {
    move_checker checker;

    EXPECT_EQ(checker.copies(), 0);
    EXPECT_EQ(checker.moves(), 0);

    std::cout << "test main: " << std::this_thread::get_id() << std::endl;

    std::future<void> task = std::async(
            std::launch::async,
            printContents<move_checker>,
                    std::ref(checker)
            );

    task.wait();
    EXPECT_EQ(checker.copies(), 0);
    EXPECT_EQ(checker.moves(), 0);
}


// forward our move_checker to count moves/copies
template <typename T>
int forwardToLambda(T&& checker) {
    auto lambda = [](T&& checker) mutable {
        return checker.payload[0];
    };

    return lambda(std::forward<T>(checker));
}

TEST(MOVE_CHECKER, forward) {
    move_checker checker;

    EXPECT_EQ(checker.copies(), 0);
    EXPECT_EQ(checker.moves(), 0);

    forwardToLambda(checker);

    EXPECT_EQ(checker.copies(), 0);
    EXPECT_EQ(checker.moves(), 0);
    // 在 Linux 上是 1 次，在 Mac 上是 2 次。 what's the reason?
    EXPECT_EQ(checker.moves(), 2);
}

