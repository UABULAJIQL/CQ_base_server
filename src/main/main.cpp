#include <iostream>
#include <thread>

// #include "thread/thread.h"
// #include "thread/threadCollector.h"
#include "thread/threadMgr.h"

int main() {

    auto threadMgr = ThreadMgr::instance();
    threadMgr->createThread(ThreadType::MainThread, 2);
    threadMgr->createThread(ThreadType::ListenThread, 2);
    threadMgr->startAll();
    //
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //
    threadMgr->stopAll();
    threadMgr->releaseRes();
    threadMgr->destroyInstance();

    return 0;
}
