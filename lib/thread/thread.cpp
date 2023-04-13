#include "thread.h"
#include <iostream>

Thread::Thread(ThreadType threadType)
    : _threadState(ThreadState::Init), _threadType(threadType) {}

void Thread::start() {
    // 给线程绑定函数
    _thread = std::thread([this]() {
        _threadState = ThreadState::Run;

        while (!(ThreadState::Stop == _threadState)) {

            if (ThreadType::MainThread == _threadType) {
                std::cout << "这是一个main线程\n";
            } else if (ThreadType::ListenThread == _threadType) {
                std::cout << "这是一个监听线程\n";
            } else {
                std::cout << "懒得写\n";
            }

            // update();

            // 缓冲减少一下循环频率
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        _threadState = ThreadState::Destroy;
    });
}

void Thread::stop() { _threadState = ThreadState::Stop; }

void Thread::releaseRes() {
    if (ThreadState::Destroy != _threadState) {
        std::cout << "线程未结束 拒绝销毁" << std::endl;
    }

    if (_thread.joinable()) {
        _thread.join();
    }
    std::cout << "线程释放结束" << std::endl;
}
ThreadState Thread::getState() const { return _threadState; }
