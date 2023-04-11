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
    for (const auto &temp : _pools) {
        temp.second->releaseRes();
        delete temp.second;
    }
    _pools.clear();
}
