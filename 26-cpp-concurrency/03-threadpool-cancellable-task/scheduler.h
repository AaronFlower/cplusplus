#ifndef SCHEDULER_H__
#define SCHEDULER_H__
#include <future>
#include <memory>
#include <string>
#include <vector>
#include "ThreadPool.h"
#include "task.h"

using namespace std;


class scheduler
{
public:
    static vector<int> addTask(shared_ptr<ThreadPool> pool, const string& name) {
        vector<future<int>> results;
        vector<task> tasks;
        int count = 15000;
        for (int i = 0; i < count; ++i) {
            task t(name + " " + to_string(i) + "\t");
            tasks.push_back(t);
            results.push_back(pool->enqueue(t));
        }

        vector<int> res(count, 0);
        auto rit = res.begin();
        auto tit = tasks.begin();

        std::this_thread::sleep_for(chrono::milliseconds(10));


        for (auto it = results.begin(); it != results.end(); ++it, ++rit) {
            if (it->wait_for(std::chrono::nanoseconds(0)) == std::future_status::ready) {
                /* cout << "ready ...." << it->get() << endl; */
                /* res.insert(rit, 1); */
                /* res.insert(rit, 0); */
            } else {
                tit->cancel();
            }
        }
        return res;
    }

};

#endif /* ifndef SCHEDULER_H__*/
