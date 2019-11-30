#ifndef LUISEREBII_VECTOR_H
#define LUISEREBII_VECTOR_H

#include <memory>

namespace lsb {

template <class T>
class vector {

    public:
        vector(): head(0), tail(0) { } 

        void push_back(T e);

    private:
        T* head;
        T* tail;

        void construct();
        void destroy();

};


template <class T>
void vector<T>::push_back(T e) {
    
}


}

#endif
