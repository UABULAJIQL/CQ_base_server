#ifndef _I_INPOOLOBJ_H
#define _I_INPOOLOBJ_H

#include "tools/I_release.h"

template <typename... Targs> class IInPoolObj : public IRelease {
  public:
    // 拿出池的时候初始化
    virtual void init(Targs... args) = 0;

    // 回归池中的时候释放清空资源
    virtual void clearn() = 0;

    virtual ~IInPoolObj() = default;
};

#endif
