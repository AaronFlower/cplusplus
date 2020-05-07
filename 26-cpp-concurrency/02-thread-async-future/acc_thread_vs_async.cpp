#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <chrono>
#include <future>
#include <string>

using namespace std;

using int_futures = vector<future<int>>;

/**
 * Using async will utilize the old empty thread if there is a thread available.
 */
int accumulate_block_worker_ret(int* data, size_t count) {
    cout << "accumulate_block_worker_ret thread_id :" << this_thread::get_id() << endl;
    cout << "sleep 2s ..." << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    return accumulate(data, data + count, 0);
}

void use_worker_in_std_async(const vector<int>& v) {
    vector<int> data(v);
    future<int> f = async(launch::async, accumulate_block_worker_ret, data.data(), data.size());
    string out_str = "use worker in std async computed " + to_string(f.get()) + "\n";
    cout << out_str ;
}

int_futures launch_split_workers_with_std_async(vector<int>& v) {
    int_futures futures;
    futures.push_back(async(launch::async, accumulate_block_worker_ret, v.data(), v.size() / 2));
    futures.push_back(async(launch::async, accumulate_block_worker_ret, v.data() + v.size() / 2, v.size() / 2));
    return futures;
}


/**
 * Using thread is often more cumbersome than we'd want,
 * and also more error-prone than we'd want.
 *
 * thread doesn't have a return value, so we must use a pointer to receive the
 * value. It's dangerous!
 */
void accumulate_block_worker(int* data, size_t count, int *result) {
    *result = accumulate(data, data + count,  0);
    cout << "accumulate_block_worker thread_id :" << this_thread::get_id() << endl;
    cout << "sleep 2s ..."  << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
}


void use_worker_in_std_thread(const vector<int>& v) {
    int result;
    vector<int> data(v);

    thread worker(accumulate_block_worker, data.data(), data.size(), &result);
    use_worker_in_std_async(v);
    worker.join();
    cout << "use worker in std thread computed: " << result << "\n";
}


vector<thread> launch_split_workers_with_std_thread(vector<int>& v, vector<int>* results) {
    vector<thread> threads;
    threads.emplace_back(accumulate_block_worker, v.data(), v.size() / 2, &((*results)[0]));
    threads.emplace_back(accumulate_block_worker, v.data() + v.size() / 2, v.size() / 2, &((*results)[1]));
    return threads;
}

int main()
{
    cout << "[+] main thread_id :" << this_thread::get_id() << endl;
    vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> results(2, 0);

    vector<thread> threads = launch_split_workers_with_std_thread(data, &results);

    for (auto& t : threads) {
        t.join();
    }

    cout << "results from launch_split_workers_with_std_thread: "
        + to_string(results[0])
        + " and "
        + to_string(results[1]) << endl;

    int_futures futures = launch_split_workers_with_std_async(data);

    cout << "results from launch_split_workers_with_std_async: "
        + to_string(futures[0].get())
        + " and "
        + to_string(futures[1].get()) << endl;

    /* use_worker_in_std_async(); */
    use_worker_in_std_thread(data);
    return 0;
}
