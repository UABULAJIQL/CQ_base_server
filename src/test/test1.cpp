#include <iostream>

#include "objPool/I_inPoolObj.h"
#include "objPool/objPool.hpp"

class A : public IInPoolObj<int, int> {
  public:
    // A() = default;
    A(int a = 1, int b = 2) : _a(a), _b(b) {}
    int _a, _b;
    void print() { std::cout << _a << ":" << _b << std::endl; }
    void init(int a, int b) override {
        // std::cout << "出池子喽" << std::endl;
        _a = a;
        _b = b;
    }
    void clearn() override {
        // std::cout << "清空释放资源" << std::endl;
    }
};

int main() {

    ObjPool<A> p(true, 3);
    p.show();

    auto *a1 = p.mallocObj(6, 6);
    auto *a2 = p.mallocObj(6, 6);
    auto *a3 = p.mallocObj(6, 6);
    // 扩容到6
    auto *a4 = p.mallocObj(6, 6);
    auto *a5 = p.mallocObj(6, 6);
    auto *a6 = p.mallocObj(6, 6);
    // 扩容到12
    auto *a7 = p.mallocObj(6, 6);
    p.show();
    p.update();
    p.show();

    // 休息5个
    //工作就2个 空闲10个
    p.freeObj(a1);
    p.freeObj(a2);
    p.freeObj(a3);
    p.freeObj(a4);
    p.freeObj(a5);

    p.show();
    // 收缩 自由个数为2
    p.update();
    p.show();

    return 0;
}
