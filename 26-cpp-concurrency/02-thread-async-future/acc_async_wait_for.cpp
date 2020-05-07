#include <iostream>
#include <numeric>
#include <thread>
#include <future>
#include <chrono>
#include <vector>


int acc_block_worker_ret(int *data, size_t count) {
    std::cout << "[+] worker thread id:" << std::this_thread::get_id() << std::endl;;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return std::accumulate(data, data + count, 0);
}

int main()
{
    std::cout << "[+] main thread id:" << std::this_thread::get_id() << std::endl;
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::future<int> f = std::async(std::launch::async, acc_block_worker_ret,
            v.data(), v.size());

    while(f.wait_for(std::chrono::milliseconds(500)) != std::future_status::ready) {
        std::cout << "...still not ready\n";
    }
    std::cout << "computed : " << f.get() << std::endl;

    return 0;
}
