//
// Created by Dalio on 2020/5/2.
//

#ifndef A8_G_LOCK_HPP
#define A8_G_LOCK_HPP

#include <iostream>
#include <mutex>

using namespace std;
namespace a8 {
    class EDOGLock {
    public:
        static std::mutex s_mtx;
        static int count;
    public:
        EDOGLock() {
            s_mtx.lock();
            count++;
            if (count > 1) {
                throw exception();
            }
        }

//        void Unlock() {
//            count--;
//            s_mtx.unlock();
//        }

        ~EDOGLock() {
            count--;
            s_mtx.unlock();
        }
    };
}
#endif //A8_G_LOCK_HPP
