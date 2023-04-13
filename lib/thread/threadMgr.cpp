#include "threadMgr.h"
void ThreadMgr::createThread(ThreadType threadType, size_t num) {
    auto iTemp = _threadCollectors.find(threadType);
    // 没有找到 重新插入定义
    if (iTemp == _threadCollectors.end())
        _threadCollectors.emplace(threadType, new ThreadCollector(threadType, num));
    else // 找到了添加数量
        iTemp->second->createThread(num);
}

void ThreadMgr::startAll() const {
    for (const auto &temp : _threadCollectors) {
        temp.second->startAll();
    }
}
void ThreadMgr::stopAll() const {
    for (const auto &temp : _threadCollectors) {
        temp.second->stopAll();
    }
}
void ThreadMgr::releaseRes() {
    for (const auto &temp : _threadCollectors) {
        temp.second->releaseRes();
    }

    std::cout << "线程管理 资源释放结束" << std::endl;
}
