#ifndef TASK_H__
#define TASK_H__ value

#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <mutex>
#include <atomic>

using std::cout;
using std::to_string;
using std::stringstream;
using std::string;

class task
{
public:
    task()=default;
    task(const task& t) {
        std::lock_guard<std::mutex> lock(m);
        name = t.name;
    };

    int operator()() {
        if (cancelled) {
            cout << "cancelled \n";
            return 0;
        } else {

        stringstream ss;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ss << std::this_thread::get_id();
        cout << "[+] " + name +" executor thread id: " + ss.str() + "\n";
       }
       return 1;
    }

    void cancel() {
        std::lock_guard<std::mutex> lock(m);
        cancelled = true;
    }

private:
    string name = "task";
    bool cancelled{false};
    std::mutex m;
};
#endif /* ifndef TASK_H__ */
