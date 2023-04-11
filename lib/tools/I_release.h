#ifndef _I_RELEASE_H
#define _I_RELEASE_H

class IRelease {
  public:
    virtual void releaseRes() = 0;
    virtual ~IRelease() = default;
};

#endif
