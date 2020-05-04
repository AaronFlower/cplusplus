#include <thread>
#include <iostream>

using std::cout, std::endl;
using std::thread;

/**
 * c++11 中为我们提供了 `thread` 线程库，这样就不用我们使用 c 风格的线程函数
 * 来编译平台无关的高并发的代码了。
 */
void foo (){
    cout << "Hello thread from function " << endl;
}

struct HelloThread {
    void operator()() {
        cout << "Hello thread from operator" << endl;
    }
};

int main(int argc, char *argv[])
{
    cout << "main begin" << endl;

    thread t1([] {
            cout << "Hello thread from lambda!" << endl;
            });

    HelloThread h;
    thread t2(h);

    thread t3(foo);

    // 等待 thread 来 join.
    t1.join();
    t2.join();
    t3.join();

    cout << "main end" << endl;

    return 0;
}
