#ifndef LUISEREBII_VECTOR_H
#define LUISEREBII_VECTOR_H

#include <algorithm>
#include <memory>

namespace lsb {

template <class T>
class vector {

    public:
        typedef size_t size_type;

        vector(): head(0), avail(0), tail(0) { } 
        
        size_t size();
        void push_back(T e);

    private:
        T* head;
        T* avail;
        T* tail;

        std::allocator<T> alloc;

        void construct();
        void append(T e);
        void destroy();

};

template <class T>
size_type vector<T>::size() {
    return avail - head;
}

template <class T>
void vector<T>::push_back(T e) {
    append(e);
}

template <class T>
void vector<T>::append(T e) {
    //If capacity has been reached
    if(avail == tail) {
        size_type old_size = size();
        //Double size
        size_type sz = std::max(1, 2 * size());
        //Allocate new space
        T* n = alloc.allocate(sz);
        //Copy
        std::uninitialized_copy(head, avail, n);
        //Destroy
        destroy();
        //Set new values appropriately
        head = n;
        avail = n + old_size;
        tail = n + sz;

        //Append
        alloc.construct(avail, e);
        ++avail;
        
    } else {
        alloc.construct(avail, e);
        ++avail;
    }

}

template <class T>
void vector<T>::destroy() {
    size_type sz = size();
    T* h = head;
    while(h != avail) {
        alloc.destroy(h++);
    }
    alloc.destroy(head, sz);
}

}

#endif
