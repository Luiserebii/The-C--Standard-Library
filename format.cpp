/**
 * <algorithm> of the C++ STL.
 *
 * Copyright (C) 2019 Luiserebii
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LUISEREBII_VECTOR_H
#define LUISEREBII_VECTOR_H

#include <algorithm>
#include <memory>
#include <stdexcept>

namespace lsb {

template <class T>
class vector {

  public:
    typedef T value_type;

    typedef T* iterator;
    typedef const T* const_iterator;

    typedef T& reference;
    typedef const T& const_reference;

    typedef size_t size_type;

    typedef std::allocator<T> allocator_type;

    /**
         * Constructors
         */
    vector();
    vector(size_type n, const T& val);
    vector(T* b, T* e);

    /**
         * Copy, assign, destroy
         */
    vector(const vector&);
    vector& operator=(const vector&);
    ~vector();

    /**
         * Iterators
         */
    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    /**
         * Capacity
         */
    size_type size() const;
    size_type max_size() const;
    bool empty() const;
    size_type capacity() const;

    /**
         * Element access
         */
    reference operator[](size_type n);
    const_reference operator[](size_type n) const;

    reference at(size_type n);
    const_reference at(size_type n) const;

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    /**
         * Modifiers
         */
    void push_back(T e);
    void pop_back();
    void clear();

    /**
         * Allocator
         */
    allocator_type get_allocator() const;

  private:
    T* head;
    T* avail;
    T* tail;

    std::allocator<T> alloc;

    void construct(T* b, T* e);
    void construct(size_type n, const T& val);
    void append(T e);
    void destroy();
};

/**
 * Constructors
 */
template <class T>
vector<T>::vector() : head(0), avail(0), tail(0) {}

template <class T>
vector<T>::vector(size_type n, const T& val) {
    construct(n, val);
}

template <class T>
vector<T>::vector(T* b, T* e) {
    construct(b, e);
}

/**
 * Copy, assign, destroy
 */
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

/**
 * Iterators
 */

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

/**
 * Capacity
 */
template <class T>
typename vector<T>::size_type vector<T>::size() const {
    return avail - head;
}

template <class T>
typename vector<T>::size_type vector<T>::max_size() const {
    return (size_t) -1;
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() const {
    return tail - head;
}

template <class T>
bool vector<T>::empty() const {
    return size() == 0;
}

/**
 * Element access
 */
template <class T>
typename vector<T>::reference vector<T>::operator[](size_type n) {
    if(head + n < avail) {
        return *(head + n);
    } else {
        throw std::out_of_range("at(): Attempting to access element out of bounds!");
    }
}

template <class T>
typename vector<T>::const_reference vector<T>::operator[](size_type n) const {
    if(head + n < avail) {
        return *(head + n);
    } else {
        throw std::out_of_range("at(): Attempting to access element out of bounds!");
    }
}

template <class T>
typename vector<T>::reference vector<T>::at(typename vector<T>::size_type n) {
    return (*this)[n];
}

template <class T>
typename vector<T>::const_reference vector<T>::at(typename vector<T>::size_type n) const {
    return (*this)[n];
}

template <class T>
typename vector<T>::reference vector<T>::front() {
    return *head;
}

template <class T>
typename vector<T>::const_reference vector<T>::front() const {
    return *head;
}

template <class T>
typename vector<T>::reference vector<T>::back() {
    return *(avail - 1);
}

template <class T>
typename vector<T>::const_reference vector<T>::back() const {
    return *(avail - 1);
}

/**
 * Modifiers
 */

template <class T>
void vector<T>::push_back(T e) {
    append(e);
}

template <class T>
void vector<T>::pop_back() {
    if(size() != 0) {
        alloc.destroy(avail - 1);
        --avail;
    }
}

template <class T>
void vector<T>::clear() {
    destroy();
}

/**
 * Allocator
 */
template <class T>
typename vector<T>::allocator_type vector<T>::get_allocator() const {
    return alloc;
}

/**
 * Private - Implementation
 */

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
    }

    //Append
    alloc.construct(avail++, e);
}

template <class T>
void vector<T>::construct(T* b, T* e) {
    //Allocate
    typename vector<T>::size_type sz = e - b;
    head = alloc.allocate(sz);
    avail = tail = head + sz;
    std::uninitialized_copy(b, e, head);
}

template <class T>
void vector<T>::construct(size_type n, const T& val) {
    head = alloc.allocate(n);
    avail = tail = head + n;
    std::uninitialized_fill(head, avail, val);
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
