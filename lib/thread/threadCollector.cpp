#include "threadCollector.h"
#include <iostream>

ThreadCollector::ThreadCollector(ThreadType threadType, size_t initNum)
    : _threadType(threadType) {

    createThread(initNum);
}
void ThreadCollector::createThread(size_t num) {
    for (size_t i = 0; i < num; ++i) {
        _threads.emplace_back(new Thread(_threadType));
    }
}

void ThreadCollector::startAll() const {
    for (const auto &temp : _threads) {
        temp->start();
    }
}
void ThreadCollector::stopAll() const {
    for (const auto &temp : _threads) {
        temp->stop();
    }
}

bool ThreadCollector::isThreadStateDestroy() {

    if (_threads.empty())
        return true;

    bool allIs = true;
    for (const auto &temp : _threads) {
        if (ThreadState::Destroy != temp->getState())
            allIs = false;
    }

    return allIs;
}

void ThreadCollector::releaseRes() {

    // 一定要全部都是销毁状态的时候才销毁
    // 先这样写着
    while (!isThreadStateDestroy())
        ;

    std::cout << "线程销毁准备" << std::endl;

    // 如果为空
    if (_threads.empty())
        return;

    // 销毁所有线程
    for (const auto &temp : _threads) {
        temp->releaseRes();
    }

    std::cout <<  "同类型的线程释放结束" << std::endl;
}
