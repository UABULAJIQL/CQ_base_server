#ifndef _I_OBJPOOL_H
#define _I_OBJPOOL_H

#include "tools/I_release.h"

// 这个类没啥用就是为了 可以存储到objPoolMgr中的容器中
class IObjPool : public IRelease {
  public:
    virtual void update() = 0;
    virtual void show() const = 0;
    virtual ~IObjPool() = default;
};

#endif
