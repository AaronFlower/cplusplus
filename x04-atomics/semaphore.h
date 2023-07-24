#include <atomic>
#include <cassert>
#include <semaphore.h>

class Semaphore
{
private:
    sem_t m_sema;

    Semaphore(const Semaphore& other) = delete;
    Semaphore& operator=(const Semaphore& other) = delete;

public:
    Semaphore(int initialCount = 0)
    {
        assert(initialCount >= 0);
        sem_init(&m_sema, 0, initialCount);
    }

    ~Semaphore()
    {
        sem_destroy(&m_sema);
    }

    void wait()
    {
        // http://stackoverflow.com/questions/2013181/gdb-causes-sem-wait-to-fail-with-eintr-error
        int rc;
        do
        {
            rc = sem_wait(&m_sema);
        }
        while (rc == -1 && errno == EINTR);
    }

    void signal()
    {
        sem_post(&m_sema);
    }

    void signal(int count)
    {
        while (count-- > 0)
        {
            sem_post(&m_sema);
        }
    }
};

class LightweightMutex
{
private:
    std::atomic<int> m_contention;         // The "box office"
    Semaphore m_semaphore;                 // The "bouncer"

public:
    void lock()
    {
        if (m_contention.fetch_add(1, std::memory_order_acquire) > 0)  // Visit the box office
        {
            m_semaphore.wait();     // Enter the wait queue
        }
    }

    void unlock()
    {
        if (m_contention.fetch_sub(1, std::memory_order_release) > 1)  // Visit the box office
        {
            m_semaphore.signal();   // Release a waiting thread from the queue
        }
    }
};
