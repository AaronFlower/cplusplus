#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <memory>
#include "ThreadPool.h"
#include "task.h"
#include "scheduler.h"

using std::vector;
using std::future;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::shared_ptr;

using int_futures = vector<future<int>>;

int_futures addTask(shared_ptr<ThreadPool> pool, const string& taskName) {
    int_futures results;
    for (int i = 0; i < 150; ++i) {
        task t(taskName);
        results.push_back(pool->enqueue(t));
    }

    return results;
}



int main()
{
    cout << "[+] main thread: " << std::this_thread::get_id() << endl;

    shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>(2);

    vector<int> res = scheduler::addTask(pool, "task-a");


    /* for (auto n : res) { */
    /*     cout << to_string(n) + "\t"; */
    /* } */
    /* cout << endl; */

    std::this_thread::sleep_for(chrono::minutes(10));

    /* vector<future<int_futures>> tasks_results; */
    /* for (int i = 0; i < 10; ++i) { */
    /*     future<int_futures> results = std::async(addTask, pool, "task-a" + to_string(i)); */
    /*     tasks_results.push_back(results); */
    /* } */


    /* string out_str; */
    /* for (int i = 0; i < 150; ++i) { */
    /*     out_str =  "result :" + to_string(i)  +  " " + to_string(results[i].get()); */
    /*     cout << out_str << endl; */
    /* } */

    return 0;
}
