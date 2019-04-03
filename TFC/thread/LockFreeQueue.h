#ifndef LOCKFREEQUEUE_H_INCLUDED
#define LOCKFREEQUEUE_H_INCLUDED

#include <atomic>
#include <memory>

namespace TFC {
template<typename T>
class LockFreeQueue {
    using Uint64 = uint64_t;
    struct CounterNode;
    struct InterCount {
        Uint64 interCounter, outerCounter;
    };
    struct Node {
        std::atomic<T*> data;
        std::atomic<InterCount> counter;
        CounterNode next;
        Node() {
            data = nullptr;
            counter.store((InterCount){0,2});
            next.externCounter = 0;
            next.next = nullptr;
        }
        void ReleaseRef() {
            InterCount oldCounter = counter.load();
            InterCount newCounter;
            do {
                newCounter = oldCounter;
                --newCounter.interCounter;
            } while(!counter.compare_exchange_strong(oldCounter, newCounter, std::memory_order_acquire, std::memory_order_relaxed));
            if(!newCounter.interCounter && !newCounter.outerCounter) {
                delete this;
            }
        }
    };
    struct CounterNode {
        Node* next;
        Uint64 externCounter;
    };
public:
     // Construction & Destruction
    LockFreeQueue() {
        CounterNode newNode;
        newNode.next = new Node();
        newNode.externCounter = 1;
        head.store(newNode);
        tail.store(newNode);
        qSize.store(0);
    }
    LockFreeQueue(const LockFreeQueue&) = delete;
    ~LockFreeQueue() {
        while (Pop() != nullptr);
    }
     // Control
    void Push(T data) {
        std::unique_ptr<T> pData(new T(data));
        CounterNode newNode;
        newNode.next = new Node();
        newNode.externCounter = 1;
        CounterNode tailNode = tail.load();
        while (1) {
            IncreaseOutCount(tail, tailNode);
            T* tData = nullptr;
            if (tailNode.next->data.compare_exchange_strong(tData, pData.get())) {
                tailNode.next->next = newNode;
                tailNode = tail.exchange(newNode);
                FreeOutCount(tailNode);
                pData.release();
                qSize.fetch_add(1);
                break;
            }
            tailNode.next->ReleaseRef();
        }
    }
    std::unique_ptr<T> Pop() {
        CounterNode headNode = head.load(std::memory_order_relaxed);
        while (1) {
            IncreaseOutCount(head, headNode);
            Node* pNode = headNode.next;
            if (pNode == tail.load().next) {
                pNode->ReleaseRef();
                return nullptr;
            }
            if (head.compare_exchange_strong(headNode, pNode->next)) {
                T* data = pNode->data.exchange(nullptr);
                FreeOutCount(headNode);
                qSize.fetch_add(-1);
                return std::unique_ptr<T>(data);
            }
            pNode->ReleaseRef();
        }
    }
    Uint64 GetSize() {
        return qSize.load(std::memory_order_relaxed);
    }
private:
    std::atomic<CounterNode> head;
    std::atomic<CounterNode> tail;
    std::atomic<Uint64> qSize;
    void IncreaseOutCount(std::atomic<CounterNode>& headNode, CounterNode& node) {
        CounterNode newNode;
        do {
            newNode = node;
            ++newNode.externCounter;
        } while(!headNode.compare_exchange_strong(node, newNode, std::memory_order_acquire, std::memory_order_relaxed));
        node = newNode;
    }
    void FreeOutCount(CounterNode& node) {
        Node* pNode = node.next;
        int cout_realease = node.externCounter - 2;
        InterCount counter = pNode->counter.load(std::memory_order_relaxed);
        InterCount newCounter;
        do {
            newCounter = counter;
            newCounter.interCounter += cout_realease;
            --newCounter.outerCounter;
        } while(!pNode->counter.compare_exchange_strong(counter, newCounter, std::memory_order_acquire, std::memory_order_relaxed));
        if (!newCounter.interCounter && !newCounter.outerCounter) {
            delete pNode;
        }
    }
};
} // TFC

#endif // LOCKFREEQUEUE_H_INCLUDED
