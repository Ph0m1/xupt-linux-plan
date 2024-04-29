#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class ThreadPool {
public:
  ThreadPool(int numThreads) : stop(false) {
    for (int i = 0; i < numThreads; i++) {
      threads.emplace_back([this] { // 线程不支持拷贝
        while (1) {
          std::unique_lock<std::mutex> lock(mtx);
          condition.wait(lock, [this] { return stop || !tasks.empty(); });
          if (stop && tasks.empty()) {
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
  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(mtx); // stop共享，须加锁
      stop = true;
    }

    condition.notify_all();
    for (auto &t : threads) {
      t.join();
    }
  }
  void wait() {
    std::unique_lock<std::mutex> lock(mtx);
    condition.wait(lock, [this] { return tasks.empty(); });
  }

  template <class F, class... Args>
  auto enqueue(F &&f, Args &&...args) -> std::future<decltype(f(args...))> {
    std::future<decltype(f(args...))> res;
    auto task = std::make_shared<std::packaged_task<decltype(f(args...))()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(mtx);
      tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
  }

private:
  std::vector<std::thread> threads;
  std::queue<std::function<void()>> tasks; // 任务队列

  std::mutex mtx; // lock
  std::condition_variable condition;

  bool stop;
};
