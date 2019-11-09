#ifndef ELIB_QUEUE__
#define ELIB_QUEUE__

#include <vector>
using std::vector;

namespace elib
{
    template <typename T>
    class Queue {
    public:
        Queue() {};
        ~Queue() = default;

        void push(T& t);
        T pop();

        size_t size() {
            return data.size();
        }

        bool empty() {
            return data.size() == 0;
        }

    private:
        vector<T> data;
    };

    template <typename T>
    void Queue<T>::push(T& t) {
        data.push_back(t);
    }

    template <typename T>
    T Queue<T>::pop() {
        if (data.size() > 0) {
            T t = data[data.size() - 1];
            data.erase(data.begin() + data.size() - 1);
            return t;
        }
        return nullptr;
    }
}

#endif /* ifndef ELIB_QUEUE__ */
