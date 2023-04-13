#ifndef _I_OBJPOOL_H
#define _I_OBJPOOL_H

#include "tools/I_release.h"

class IObjPool : public IRelease {
  public:
    virtual void update() = 0;
    virtual void show() const = 0;
    virtual ~IObjPool() = default;
};

#endif
