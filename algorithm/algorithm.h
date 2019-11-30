#ifndef LUISEREBII_ALGORITHM_H
#define LUISEREBII_ALGORITHM_H

namespace lsb {

template <class In>
bool equal(In begin, In end, In begin2) {
    while(*begin != *end) {
        if(*begin != *begin2) {
            return false;
        }
        ++begin, ++begin2;
    }
    return true;
}

template <class In, class T>
In find(In begin, In end, T val) {
    while(begin != end && *begin != val) {
        ++begin;
    }
    return begin;
}

#endif
