#ifndef LUISEREBII_VECTOR_H
#define LUISEREBII_VECTOR_H

#include <algorithm>
#include <memory>
#include <stdexcept>

namespace lsb {

template <class T>
class vector {

    public:
        typedef T* iterator;
        typedef const T* const_iterator;

        typedef size_t size_type;

        vector();

        //Copy, assign, destroy
        vector(const vector&);
        vector& operator=(const vector&);
        ~vector();

        T& operator[](size_type n);
        const T& operator[](size_type n) const;

        size_type size() const;
        
        T& at(size_type n);
        const T& at(size_type n) const;

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


//Constructors
template <class T>
vector<T>::vector(): head(0), avail(0), tail(0) {
    
}

//Copy, assign, destroy
template <class T>
vector<T>::vector(const vector& rhs) {
    
}

template <class T>
vector<T>& vector<T>::operator=(const vector& rhs) {
    //Check for self-assignment
    if(&rhs != this) {
        //Destroy the left-hand side
        destroy();
        //Construct from the right
        construct(rhs.begin(), rhs.end());
    }
}

template <class T>
vector<T>::~vector() {
    destroy();
}

template <class T>
typename vector<T>::size_type vector<T>::size() const {
    return avail - head;
}

template <class T>
T& vector<T>::operator[](size_type n) {
    if(head + n < avail) {
        return *(head + n);
    } else {
        throw std::out_of_range("at(): Attempting to access element out of bounds!");
    }
}

template <class T>
const T& vector<T>::operator[](size_type n) const {
    if(head + n < avail) {
        return *(head + n);
    } else {
        throw std::out_of_range("at(): Attempting to access element out of bounds!");
    }
}

template <class T>
T& vector<T>::at(typename vector<T>::size_type n) {
    return (*this)[n];
}

template <class T>
const T& vector<T>::at(typename vector<T>::size_type n) const {
    return (*this)[n];
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
        size_type sz = std::max(1UL, 2 * size());
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
    alloc.deallocate(head, sz);
    head = avail = tail = 0;
}

}

#endif
