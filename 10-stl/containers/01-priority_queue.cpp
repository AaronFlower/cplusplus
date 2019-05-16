#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::vector;
using std::priority_queue;

template<typename T>
void print_queue(T &q) {
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
}

int main(void)
{
    priority_queue<int> q;

    for (auto i : {1, 8, 5, 9, 10, 1, 3}) {
       q.push(i);
    }

    print_queue(q);

    return 0;
}
