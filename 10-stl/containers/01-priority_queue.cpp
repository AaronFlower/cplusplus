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
    priority_queue<int, vector<int>, std::greater<int>> q2;

    int k = 0;
    for (auto i : {1, 8, 5, 9, 10, 1, 3}) {
       q.push(i);
       q2.push(i);
        if (k++ > 2) {
            q.pop();
            q2.pop();
        }
    }

    print_queue(q);
    cout << std::endl;
    print_queue(q2);

    return 0;
}
