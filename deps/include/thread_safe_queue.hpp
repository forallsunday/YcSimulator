#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>

/**
 * @brief 线程安全的队列
 *
 * 该队列使用互斥锁和条件变量保证线程安全
 *
 * @tparam T 队列元素类型
 */
template <typename T>
class ThreadSafeQueue {
  public:
    /**
     * @brief 将元素推入队列（阻塞直到有空间）
     *
     * @param value 要入队的元素
     */
    void push(T value) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(value));
        }
        condition_.notify_one();
    }

    /**
     * @brief 尝试从队列中取出元素（非阻塞）
     *
     * @param value 用于存储取出的元素
     * @return true=如果成功取出元素，false=如果队列为空
     */
    bool tryPop(T &value) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return false;
        }
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    /**
     * @brief 从队列中取出元素（阻塞等待直到有元素）
     *
     * @param value 用于存储取出的元素
     */
    void waitAndPop(T &value) {
        std::unique_lock<std::mutex> lock(mutex_);
        // 等待队列非空
        condition_.wait(lock, [this] { return !queue_.empty(); });
        value = std::move(queue_.front());
        queue_.pop();
    }

    /**
     * @brief 从队列中取出元素（带超时时间的阻塞等待）
     *
     * @param value 用于存储取出的元素
     * @param timeout 等待的超时时间
     * @return true=如果成功取出元素，false=如果队列为空且超时
     */
    bool waitForAndPop(T &value, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mutex_);

        // 等待直到队列非空或超时
        if (!condition_.wait_for(lock, timeout, [this]() { return !queue_.empty(); })) {
            // 超时仍然为空
            return false;
        }

        // 有元素可以取
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    /**
     * @brief 通知所有等待的线程
     */
    void notifyAll() {
        std::lock_guard<std::mutex> lock(mutex_);
        condition_.notify_all();
    }

    /**
     * @brief 检查队列是否为空
     *
     * @return true 如果队列为空，false 否则
     */
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    /**
     * @brief 获取队列中元素的数量
     *
     * @return 队列中元素的数量
     */
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    void clearAndNotify() {
        std::lock_guard<std::mutex> lock(mutex_);
        while (!queue_.empty()) {
            queue_.pop();
        }
        condition_.notify_all();
    }

  private:
    std::queue<T>           queue_;     // 底层存储队列
    mutable std::mutex      mutex_;     // 保护队列的互斥锁
    std::condition_variable condition_; // 用于线程同步的条件变量
};

#endif // THREAD_SAFE_QUEUE_H