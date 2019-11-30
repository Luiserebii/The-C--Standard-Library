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
        vector(T* b, T* e);

        //Copy, assign, destroy
        vector(const vector&);
        vector& operator=(const vector&);
        ~vector();

        T& operator[](size_type n);
        const T& operator[](size_type n) const;

        size_type size() const;
        
        T& at(size_type n);
        const T& at(size_type n) const;
        iterator begin();
        const_iterator begin() const;

        iterator end();
        const_iterator end() const;

        void push_back(T e);

    private:
        T* head;
        T* avail;
        T* tail;

        std::allocator<T> alloc;

        void construct(T* b, T* e);
        void append(T e);
        void destroy();

};


//Constructors
template <class T>
vector<T>::vector(): head(0), avail(0), tail(0) {
    
}

template <class T>
vector<T>::vector(T* b, T* e) {
    construct(b, e);
}

//Copy, assign, destroy
template <class T>
vector<T>::vector(const vector& rhs) {
    construct(rhs.begin(), rhs.end());
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
typename vector<T>::iterator vector<T>::begin() {
    return head;
}

template <class T>
typename vector<T>::const_iterator vector<T>::begin() const {
    return head;
}

template <class T>
typename vector<T>::iterator vector<T>::end() {
    return avail;
}

template <class T>
typename vector<T>::const_iterator vector<T>::end() const {
    return avail;
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
void vector<T>::construct(T* b, T* e) {
    //Allocate
    typename vector<T>::size_type sz = e - b;
    T* n = alloc.allocate(sz);
    std::uninitialized_copy(b, e, n);
    head = n;
    avail = tail = n + sz;
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
