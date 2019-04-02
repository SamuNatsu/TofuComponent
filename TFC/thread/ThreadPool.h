#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "LockFreeQueue.h"

#include <mutex>
#include <atomic>
#include <future>
#include <thread>
#include <vector>
#include <functional>
#include <condition_variable>

namespace TFC {
namespace Thread {
class ThreadPool {
using Uint64 = uint64_t;
using VVF = std::function<void()>;
public:
    std::atomic<Uint64> idleThreadCount;
     // Construction & Destruction
    ThreadPool(Uint64 = 4);
    ~ThreadPool();
     // Control
    template<class T, class... Args>
    auto Commit(T&& task, Args&&... args) -> std::future<typename std::result_of<T(Args...)>::type> {
        using retType = typename std::result_of<T(Args...)>::type;
        auto pTask = std::make_shared<std::packaged_task<retType()> >(std::bind(std::forward<T>(task), std::forward<Args>(args)...));
        std::future<retType> future = pTask->get_future();
        {
            std::unique_lock<std::mutex> lock(taskMutex);
            if(stopped.load())
                throw "ERROR";
            taskPool.Push(
                [pTask]() {
                    (*pTask)();
                });
        }
        taskCV.notify_one();

        return future;
    }
private:
    std::vector<std::thread> threadPool;
    LockFreeQueue<VVF> taskPool;
    std::mutex taskMutex;
    std::condition_variable taskCV;
    std::atomic<bool> stopped;
};
} // Thread
} // TFC

#endif // THREADPOOL_H
