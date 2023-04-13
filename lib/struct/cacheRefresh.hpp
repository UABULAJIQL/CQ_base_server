#ifndef _CACHEREFRESH_H
#define _CACHEREFRESH_H

#include <iostream>

#include <forward_list>
#include <queue>
#include <set>

#include "tools/I_release.h"

// 一个数据结构
// 为了将要添加的 或者 要移除的 对象 存储起来 到下一帧 统一执行 从而减少锁

template <typename T> class CacheRefresh : public IRelease {
  public:
    // std::set<T *> *getReaderCache();

    void addObj(T *pObj);

    void removeObj(T *pObj);

    bool objsChange() const;

    // 添加的添加 移除的移除 回到自由队列
    void update(std::queue<T *> &_free);

    // 工作对象的个数
    std::size_t workObjCount() const;

    std::size_t addObjCount() const;

    std::size_t removeObjCount() const;

    void releaseRes() override;

  private:
    // 需要查找相对快点
    // 我们需要从中间移除和插入
    // 所以选择set 直接使用地址会出问题吗？ 是不是唯一的？
    // 后续可能改成map<唯一标识号, T*>!!!
    std::set<T *> _workObjs;

    // 避免扩容直接使用最简单的 单链表
    std::forward_list<T *> _adds;
    std::forward_list<T *> _removes;

    // 记录_adds和_removes中的对象个数
    size_t _addObjCount{0};
    size_t _removesObjCount{0};
};

template <typename T> void CacheRefresh<T>::addObj(T *pObj) {
    _adds.emplace_front(pObj);
    ++_addObjCount;
}

template <typename T> void CacheRefresh<T>::removeObj(T *pObj) {
    _removes.emplace_front(pObj);
    ++_removesObjCount;
}

template <typename T> bool CacheRefresh<T>::objsChange() const {
    // 有数据的话 返回true
    return !(_adds.empty() && _removes.empty());
}

template <typename T> void CacheRefresh<T>::update(std::queue<T *> &_free) {

    // 删除
    if (!_removes.empty()) {
        for (const auto temp : _removes) {
            _workObjs.erase(temp);
            _free.emplace(temp);
        }
        _removes.clear();
        _removesObjCount = 0;
    }

    if (!_adds.empty()) {
        // 添加
        // _objs.insert(_adds.begin(), _adds.end());
        for (const auto temp : _adds) {
            _workObjs.emplace(temp);
        }

        _adds.clear();
        _addObjCount = 0;
    }
}

template <typename T> std::size_t CacheRefresh<T>::workObjCount() const {
    return _workObjs.size();
}
template <typename T> std::size_t CacheRefresh<T>::addObjCount() const {
    return _addObjCount;
}
template <typename T> std::size_t CacheRefresh<T>::removeObjCount() const {
    return _removesObjCount;
}

template <typename T> void CacheRefresh<T>::releaseRes() {
    std::cout << "交换数据中的资源释放" << std::endl;
    if (0 != workObjCount()) {
        for (const auto &temp : _workObjs) {
            temp->releaseRes();
            delete temp;
        }
        _workObjs.clear();
    }
    if (0 != addObjCount()) {
        for (const auto &temp : _adds) {
            temp->releaseRes();
            delete temp;
        }
        _adds.clear();
    }
}

#endif
