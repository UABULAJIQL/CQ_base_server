#ifndef _OBJPOOL_H
#define _OBJPOOL_H


#include "I_objPool.h"
#include "struct/cacheRefresh.hpp"

#include <iostream>
#include <queue>

// 这是一个对象池类 任意T类型
// 由于打算一个线程中一个线程池管理 所以这里不使用锁
template <typename T> class ObjPool : public IObjPool {
  public:
    ObjPool(bool systolic = false, std::size_t initCount = 10);
    // ObjPool(bool systolic = true, std::size_t initCount = 3);

    // 分配对象
    template <typename... Targs> T *mallocObj(Targs... args);

    // 放回对象池
    void freeObj(T *);

    // 添加对象
    template <typename... Targs> void expansionObjs(Targs... args);

    // 更新数据
    void update() override;

    // 输出信息
    void show() const override;

    // 启动收缩
    void openSystolic();

    // 关闭收缩
    void closeSystolic();

    // 收缩
    void systolicFun();

    // 释放资源
    void releaseRes() override;

  protected:
    // 是否要自动收缩
    bool _systolic;

    // 当空闲的个数是 有用的个数的倍数 达到的话搜索容量
    std::size_t _sysMultiple{3};

    // 扩容倍数
    std::size_t _multiple{2};

    // 起始默认个数
    std::size_t _initCount;

    // 总创建的对象个数
    size_t _total{0};

    std::queue<T *> _free;

    CacheRefresh<T> _work;
};

template <typename T>
ObjPool<T>::ObjPool(bool systolic, std::size_t initCount)
    : _systolic(systolic), _initCount(initCount) {
    // 需要有无参构造函数
    // 初始扩容
    expansionObjs();
}

template <typename T>
template <typename... Targs>
T *ObjPool<T>::mallocObj(Targs... args) {

    if (_free.empty()) {
        // 可用数据为空 需要扩容
        expansionObjs();
    }

    // 出队列
    T *temp = _free.front();
    _free.pop();

    // 出对象池后 初始化
    temp->init(args...);

    // 添加到工作容器中
    _work.addObj(temp);

    return temp;
}

template <typename T> void ObjPool<T>::freeObj(T *pObj) {
    // 回到线程池之前需要将数据释放
    pObj->clearn();
    _work.removeObj(pObj);
}

template <typename T>
template <typename... Targs>
void ObjPool<T>::expansionObjs(Targs... args) {

    // 初始化
    if (0 == _total) {
        for (size_t i = 0; i < _initCount; ++i) {
            _free.push(new T(args...));
        }
        _total = _initCount;

    } else { // 按倍率扩容 扩容成两倍就是加一倍 cq无语 这里踩坑了
        for (size_t i = 0; i < _total * (_multiple - 1); ++i) {
            _free.push(new T(args...));
        }
        _total *= _multiple;
    }
}

template <typename T> void ObjPool<T>::update() {

    if (_work.objsChange()) {
        _work.update(_free);
    }

    // 收缩 要大于初始默认值
    if (_systolic && _total > _initCount)
        systolicFun();
}

template <typename T> void ObjPool<T>::show() const {
    std::cout << typeid(T).name() << "对象池中的总对象有：" << _total;
    std::cout << " 自由对象有：" << _free.size();
    std::cout << " 工作对象有：" << _work.workObjCount();
    std::cout << " 将要去工作的对象有：" << _work.addObjCount();
    std::cout << " 将要去休息的对象有：" << _work.removeObjCount() << std::endl;
}

template <typename T> void ObjPool<T>::openSystolic() { _systolic = true; }
template <typename T> void ObjPool<T>::closeSystolic() { _systolic = false; }
template <typename T> void ObjPool<T>::systolicFun() {

    std::size_t usingCount = _work.workObjCount() + _work.addObjCount();

    if (_free.size() > usingCount * _sysMultiple) {

        // 留 和有用的一样多
        while (_free.size() != usingCount) {

            // 不能比初始值小
            if (_total <= _initCount)
                break;

            delete _free.front();
            _free.pop();

            --_total;
        }
    }
}

template <typename T> void ObjPool<T>::releaseRes() {

    _work.releaseRes();

    while (!_free.empty()) {
        auto temp = _free.front();

        temp->releaseRes();

        delete temp;
        _free.pop();
    }
}

#endif
