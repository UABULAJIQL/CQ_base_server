#ifndef _THREAD_H
#define _THREAD_H

#include "tools/I_release.h"
#include <thread>

// 考虑了挺久
// 原先是想写一个可以控制暂停和重新启动的线程类
// 可以配合作为对象池的对象 就形成了对象池
// 暂停转态下的线程需要空转 这个资源消耗感觉比较大？
// 所以暂时还是实现用几个开几个的线程策略吧

enum class ThreadType {
    MainThread = 1 << 0,   // 主线程
    ListenThread = 1 << 1, // 监听线程
    ConnectThread = 1 << 2 // 连接线程

};

enum class ThreadState { Init, Run, Stop, Destroy };

class Thread : public IRelease {
  public:
    Thread(ThreadType threadType);

    // 启动线程
    void start();

    // 线程停止
    void stop();

    // 销毁 线程并且释放资源
    void releaseRes() override;

    // 获取线程状态
    ThreadState getState() const;

  private:
    // 空闲线程对象
    std::thread _thread;

    ThreadState _threadState;

    ThreadType _threadType;
};

#endif
