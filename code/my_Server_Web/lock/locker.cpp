//
// Created by heyonghu on 22-7-19.
//
#include "locker.h"

sem::sem() {

}

sem::sem(int num) {

}

sem::~sem() {

}

bool sem::wait() {
    return false;
}

bool sem::post() {
    return false;
}

locker::locker() {

}

locker::~locker() {

}

bool locker::lock() {
    return false;
}

bool locker::unlock() {
    return false;
}

pthread_mutex_t *locker::get() {
    return nullptr;
}

cond::cond() {

}

cond::~cond() {

}

bool cond::wait(pthread_mutex_t *m_mutex) {
    return false;
}

bool cond::timewait(pthread_mutex_t *m_mutex, struct timespec t) {
    return false;
}

bool cond::signal() {
    return false;
}

bool cond::broadcast() {
    return false;
}
