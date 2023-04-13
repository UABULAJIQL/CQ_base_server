#ifndef _THREADMGR_H
#define _THREADMGR_H

#include "threadCollector.h"
#include "tools/I_release.h"
#include "tools/singleton.h"
#include <map>

// 线程控制管理类

class ThreadMgr : public IRelease, public Singleton<ThreadMgr> {
  public:
    // 创建线程
    void createThread(ThreadType threadType, size_t num);

    // 启动所有线程
    void startAll() const;

    // 所有线程停止
    void stopAll() const;

    // 释放
    void releaseRes() override;

  private:
    std::map<ThreadType, ThreadCollector *> _threadCollectors;
};

#endif
