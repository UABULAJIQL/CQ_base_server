#ifndef _THREADCOLLECTOR_H
#define _THREADCOLLECTOR_H

#include "thread.h"
#include <vector>

class ThreadCollector : public IRelease {

  public:
    // 初始化 线程类型 线程数量
    ThreadCollector(ThreadType threadType, size_t initNum);

    // 创建线程
    void createThread(size_t num);

    // 启动所有线程
    void startAll() const;

    // 所有线程停止
    void stopAll() const;

    // 是否全部都是销毁转态
    bool isThreadStateDestroy();

    // 释放
    void releaseRes() override;

  protected:
    ThreadType _threadType;

    std::vector<Thread *> _threads;
};

#endif
