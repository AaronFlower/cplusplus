#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <memory>
#include "task.h"

using std::vector;
using std::future;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::shared_ptr;

using int_futures = vector<future<int>>;

int main()
{
    cout << "[+] main thread: " << std::this_thread::get_id() << endl;

    task t;
    std::thread t1(t);
    t1.join();

    return 0;
}
