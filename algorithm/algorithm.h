#ifndef LUISEREBII_ALGORITHM_H
#define LUISEREBII_ALGORITHM_H

#include <stdexcept>

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

template <class In, class Out>
Out copy(In begin, In end, Out dest) {
    while(begin != end) {
        *dest++ = *begin++;
    }
    return dest;
}

template <class In>
In search(In begin, In end, In begin2, In end2) {
    size_t size = end2 - begin2;
    //Check to see that size is larger enough
    if(end - begin < size) {
        throw std::domain_error("Range to search for too large");
    }
    //Ensure we search within the range
    while(begin + size <= end) {
        In b2 = begin2;
        for(In b = begin; b2 != end2; ++b, ++b2) {
            if(*b != *b2) {
                break;
            }
        }
        //If we hit the end, we found it~
        if(b2 == end2) {
            return begin;
        }
        ++begin;
    }
    return end;
}

}


#endif
