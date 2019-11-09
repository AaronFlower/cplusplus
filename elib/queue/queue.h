#ifndef ELIB_QUEUE__
#define ELIB_QUEUE__

#include <vector>
using std::vector;

#include <cstring>

namespace elib
{
    template <typename T>
    class Queue {
    public:
        Queue() {
            size_ = 0;
            capacity = 4;
            data = new T[capacity];
        };

        ~Queue() {
            if (data != nullptr) {
                delete []data;
            }
        }

        void push(T t);
        void pop();
        T front() const;

        size_t size() {
            return size_;
        }

        bool empty() {
            return size_ == 0;
        }

    private:
        T* data;
        size_t size_;
        size_t capacity;
    };

    template <typename T>
    void Queue<T>::push(T t) {
        if (size_ >= capacity) {
            capacity *= 2;
            T *newData = new T[capacity];
            std::memcpy(newData, data, size_ * sizeof(T));
            delete data;
            data = newData;
        }
        data[size_++] = t;
    }

    template <typename T>
    void Queue<T>::pop() {
        if (size_ > 0) {
            ++data;
            --size_;
        }
    }

    template <typename T>
    T Queue<T>::front() const {
        if (size_ > 0) {
            return data[0];
        }
        return nullptr;
    }


}

#endif /* ifndef ELIB_QUEUE__ */
