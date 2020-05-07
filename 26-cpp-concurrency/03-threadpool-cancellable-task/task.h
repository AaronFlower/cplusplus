#ifndef TASK_H__
#define TASK_H__ value

#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <mutex>
#include <cmath>

using std::cout;
using std::to_string;
using std::stringstream;
using std::string;

class task
{
public:
    task(const string& name):name(name){}

    task(const task& t) {
        std::lock_guard<std::mutex> lock(_m);
        name = t.name;
    }

    int operator()() {
        std::lock_guard<std::mutex> guard(_m);
        if (cancelled) {
           cout << "[+] " + name + "cancelled \n";
           return 0;
        } else {
           stringstream ss;
           /* std::this_thread::sleep_for(std::chrono::milliseconds(1000)); */
           /* std::this_thread::wait_for(std::chrono::milliseconds(100)); */

           /* double r = 0.0; */
           /* for (int i = 1; i < 10000000; ++i) { */
           /*     r += sqrt(i); */
           /* } */

           ss << std::this_thread::get_id();
           cout << "[+] " + name +" executor thread id: " + ss.str() + "\n";
           return 1;
       }
    }

    void cancel() {
        std::lock_guard<std::mutex> guard(_m);
        /* cout << "cancelled ... " << std::endl; */
        cancelled = true;
    }

private:
    string name{"task"};
    bool cancelled{false};
    std::mutex _m;
};
#endif /* ifndef TASK_H__ */
