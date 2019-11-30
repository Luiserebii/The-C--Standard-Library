#ifndef LUISEREBII_ALGORITHM_H
#define LUISEREBII_ALGORITHM_H

namespace lsb {

template <class In>
bool equal(In begin, In end, In begin2) {
    while(begin != end) {
        if(begin++ != begin2++) {
            return false;
        }
    }
    return true;
}


}

#endif
