#ifndef _SINGLETON_H
#define _SINGLETON_H

#include <iostream>
#include <stdexcept>

// 单例类的基类
template <typename T> class Singleton {
  public:
    template <typename... Args> static T *instance(Args &&...args) {
        if (nullptr == m_pInstance)
            m_pInstance = new T(std::forward<Args>(args)...);

        return m_pInstance;
    }

    static T *getInstance() {
        if (nullptr == m_pInstance) {
            std::cout << "没有初始化 创建实例!!!" << std::endl;
        }
        return m_pInstance;
    }
    static void destroyInstance() {
        delete m_pInstance;
        m_pInstance = nullptr;
    }

  private:
    static T *m_pInstance;
};

template <class T> T *Singleton<T>::m_pInstance = nullptr;

#endif
