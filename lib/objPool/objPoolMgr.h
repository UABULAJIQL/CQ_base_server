#ifndef _OBJPOOLMGR_H
#define _OBJPOOLMGR_H

#include <map>

#include "objPool.hpp"

class ObjPoolMgr : public IRelease {
  public:
    // 获取对象池
    template <typename T>
    IObjPool *getPool(bool systolic = false, std::size_t initCount = 10);

    // 数据更新
    void update();

    // 显示数据
    void show() const;

    // 释放资源
    void releaseRes() override;

  private:
    // 存储对象池
    std::map<std::int64_t, IObjPool *> _pools;
};
template <typename T>
IObjPool *ObjPoolMgr::getPool(bool systolic, std::size_t initCount) {

    // 获取类型的专有哈希值
    const auto typeHashCode = typeid(T).hash_code();

    auto iter = _pools.find(typeHashCode);

    if (iter != _pools.end()) {
        return iter->second;
    }

    auto pPool = new ObjPool<T>(systolic, initCount);
    _pools.emplace(std::make_pair<int64_t, IObjPool *>(typeHashCode, pPool));

    return pPool;
}

#endif
