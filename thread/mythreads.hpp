#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <vector>
#include <functional>
#include <chrono>

class ThreadPool
{
public:
    ThreadPool(int numThreads) : stop(false)
    {
        for (int i = 0; i < numThreads; i++)
        {
            threads.emplace_back([this] { // 线程不支持拷贝
                while (1)
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    condition.wait(lock, [this]
                                   { return stop || !tasks.empty(); });
                    if (stop && tasks.empty())
                    {
                        return;
                    }
                    std::function<void()> task(std::move(tasks.front()));
                    tasks.pop();
                    lock.unlock();
                    task();
                }
            });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(mtx); // stop共享，须加锁
            stop = true;
        }

        condition.notify_all();
        for (auto &t : threads)
        {
            t.join();
        }
    }

    template <class F, class... Args>
    void enqueue(F &&f, Args &&...args)
    {
        std::function<void()> task = std::bind(std::forward<F>(f), std::forward<Args>(args)...); // 使用forward实现通用引用
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::move(task)); // 将左值转化为右值
        }
        condition.notify_one();
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks; // 任务队列

    std::mutex mtx; // lock
    std::condition_variable condition;

    bool stop;
};

long long factorial(long long n){
    return n == 1 ? 1 : n * factorial(n - 1);
}

