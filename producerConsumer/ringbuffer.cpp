#include <iostream>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <unistd.h>
using namespace std;

template <size_t n, typename T>
class RingBuffer {
private:
    unique_ptr<T[]> arr;    //
    int getIndex;
    int putIndex;
    mutex mut;
    condition_variable cond;
    static const int noVal = 9999;

public:
    RingBuffer() : arr(make_unique<T[]>(n)), getIndex(0), putIndex(0) {
      for(int i = 0; i < n; ++i)
          arr[i] = noVal;
    };

    void put(T& t) {
        int index = putIndex % n;
        unique_lock<mutex> lock(mut);
        while (arr[index] != noVal)
            cond.wait(lock);        // unlocks and waits till other threads notifies it, acquires the lock again once notified

        arr[index] = t;
        cond.notify_all();          // notifies other threads waiting for same mutex. got to explicitly unlock
        lock.unlock();
        putIndex++;
    };

    T get() {
        int index = getIndex % n;
        unique_lock<mutex> lock(mut);
        while (arr[index] == noVal)
            cond.wait(lock);

        T t = arr[index];
        arr[index] = noVal;
        cond.notify_all();
        lock.unlock();
        getIndex++;
        return t;
    };
};

template<size_t n, typename T>
void producer(RingBuffer<n,T>& r) {
    for (int i = 0; i < 10; ++i)
        r.put(i);
}

template<size_t n, typename T>
void consumer(RingBuffer<n,T>& r) {
    for (int i = 0; i < 10; ++i)
        cout << r.get() << endl;
}

int main() {
    RingBuffer<5,int> r;
    thread t1(producer<5, int>, ref(r));
    thread t2(consumer<5, int>, ref(r));

    t1.join();
    t2.join();

}