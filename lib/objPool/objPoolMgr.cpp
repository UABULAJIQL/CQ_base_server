#include "objPoolMgr.h"
#include <iostream>
void ObjPoolMgr::update() {
    for (const auto &temp : _pools) {
        temp.second->update();
    }
}
void ObjPoolMgr::show() const {
    for (const auto &temp : _pools) {
        temp.second->show();
    }
}

void ObjPoolMgr::releaseRes() {
    std::cout << "对象池管理的资源释放" << std::endl;
    for (const auto &temp : _pools) {
        temp.second->releaseRes();
        delete temp.second;
    }
    _pools.clear();
}
