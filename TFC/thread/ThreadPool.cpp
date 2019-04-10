#include "ThreadPool.h"

namespace TFC {
namespace Thread {
ThreadPool::ThreadPool(Uint64 pSize) {
    idleThreadCount.store(pSize < 1 ? 1 : pSize);
    stopped.store(false);

    for (Uint64 i = 0; i < idleThreadCount.load(); ++i) {
        threadPool.emplace_back(
            [&]() {
                VVF task;
                while (1) {
                    std::unique_ptr<VVF> task;
                    {
                        std::unique_lock<std::mutex> lock(taskMutex);
                        taskCV.wait(
                            lock,
                            [&]() {
                                return stopped.load() || taskPool.GetSize() > 0;
                            });
                        if (stopped.load() && taskPool.GetSize() == 0)
                            return;
                        task = taskPool.Pop();
                    }
                    idleThreadCount.fetch_add(-1);
                    (*task)();
                    idleThreadCount.fetch_add(1);
                }
            });
    }
}

ThreadPool::~ThreadPool() {
    stopped.store(true);

    taskCV.notify_all();
    for(auto& i : threadPool) {
        if (i.joinable()) {
            i.join();
        }
    }
}
} // Thread
} // TFC
