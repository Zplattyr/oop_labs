#include <cstddef>
#include <memory>
#include <iostream>
#include "allocator.h"

template <typename T, typename Allocator = PoolAllocator<T>>
class Stack {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using pointer = typename std::allocator_traits<Allocator>::pointer;

    Stack();
    ~Stack();

    size_type get_size() const;
    size_type get_capacity() const;

    void push(const T& value);
    void pop();
    const value_type& top() const;
    value_type& top();
    void clear();
    
    // void remove(int index);

    // value_type& operator[](std::size_t index);
    // const value_type& operator[](std::size_t index) const;


    class Iterator : public std::iterator<std::forward_iterator_tag, T>{
        friend class List;
    private:
        T *item;
    public:
        
        Iterator(T* ptr);
        Iterator(Iterator &other);
        Iterator(Iterator &&other) noexcept;
        ~Iterator();

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

        T& operator*() const;
        T* operator->() const;

        Iterator& operator++();
        Iterator operator++(int);
        Iterator operator=(const Iterator& other);
        Iterator& operator =(Iterator &&other) noexcept;
    };
    

    class ConstIterator : public std::iterator<std::forward_iterator_tag, T>{
        friend class List;
    private:
        const T *item;
    public:
        
        ConstIterator(T* ptr);
        ConstIterator(ConstIterator &other);
        ConstIterator(ConstIterator &&other) noexcept;
        ~ConstIterator();

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

        const T& operator*() const;
        T* operator->() const;

        ConstIterator& operator++();
        ConstIterator operator++(int);
        ConstIterator operator=(const ConstIterator& other);
        ConstIterator& operator =(ConstIterator &&other) noexcept;
    };

    Iterator begin() const;
    Iterator end() const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;

private:
    pointer start_data_p;     
    size_type size;
    size_type capacity;
    PoolAllocator<T> allocator;

    void v_allocate(size_type new_capacity);
    void v_deallocate();
    void v_reserve(size_type new_capacity);

};

template <typename T, typename Allocator>
Stack<T, Allocator>::Stack() : start_data_p(nullptr), size(0), capacity(0), allocator() {}

template <typename T, typename Allocator>
Stack<T, Allocator>::~Stack() {
    clear();
    v_deallocate();
}

template <typename T, typename Allocator>
void Stack<T, Allocator>::pop() {
    if (size == 0) {
        throw std::out_of_range("Index out of range");
        return;
    }
 
    start_data_p[size-1] = T();
    size--;
}

template <typename T, typename Allocator>
T& Stack<T, Allocator>::top() {
    if (size == 0) {
        throw std::out_of_range("Index out of range");
    }
    return start_data_p[size-1];
}

template <typename T, typename Allocator>
const T& Stack<T, Allocator>::top() const {
    if (size == 0) {
        throw std::out_of_range("Index out of range");
    }
    return start_data_p[size-1];
}

template <typename T, typename Allocator>
void Stack<T, Allocator>::push(const T& value) {
    if (size == capacity) {
        if (capacity == 0) {v_reserve(1);}
        else {v_reserve(capacity * 2);}
    }
    allocator.construct(start_data_p + size, value);
    ++size;
}

template <typename T, typename Allocator>
size_t Stack<T, Allocator>::get_size() const {
    return size;
}

template <typename T, typename Allocator>
size_t Stack<T, Allocator>::get_capacity() const {
    return capacity;
}

template <typename T, typename Allocator>
void Stack<T, Allocator>::clear() {
    for (size_type i = 0; i < size; ++i) {
        allocator.destroy(start_data_p + i);
    }
    size = 0;
}

// template <typename T, typename Allocator>
// T& Stack<T, Allocator>::operator[](std::size_t index){
//     if ((index >= size) || (index < 0)) { throw std::out_of_range("Index out of range"); }
//     return start_data_p[index];
// }

// template <typename T, typename Allocator>
// const T& Stack<T, Allocator>::operator[](std::size_t index) const{
//     if ((index >= size) || (index < 0)) { throw std::out_of_range("Index out of range"); }
//     return start_data_p[index];
// }

template <typename T, typename Allocator>
void Stack<T, Allocator>::v_allocate(size_type new_capacity) {
    start_data_p = allocator.allocate(new_capacity);
    capacity = new_capacity;
}

template <typename T, typename Allocator>
void Stack<T, Allocator>::v_deallocate() {
    if (start_data_p != nullptr){
        allocator.deallocate(start_data_p, capacity);
        start_data_p = nullptr;
        capacity = 0;
    }
}

template <typename T, typename Allocator>
void Stack<T, Allocator>::v_reserve(size_type new_capacity) {
    if (new_capacity > capacity) {
        
        pointer new_data_p = allocator.allocate(new_capacity);
        for (size_type i = 0; i < size; ++i) {
            allocator.construct(new_data_p + i, std::move(start_data_p[i]));
            allocator.destroy(start_data_p + i);
        }
        if (capacity != 0){allocator.deallocate(start_data_p, capacity);}
        start_data_p = new_data_p;
        capacity = new_capacity;
    }
}

template <typename T, typename Allocator>
Stack<T, Allocator>::ConstIterator::ConstIterator(T* ptr) : item(ptr){}

template <typename T, typename Allocator>
Stack<T, Allocator>::ConstIterator::ConstIterator(ConstIterator &other) : item(other.item) {}

template <typename T, typename Allocator>
Stack<T, Allocator>::ConstIterator::ConstIterator(ConstIterator &&other) noexcept {
    item = std::move(other.item);
}

template <typename T, typename Allocator>
Stack<T, Allocator>::ConstIterator::~ConstIterator() = default;

template <typename T, typename Allocator>
bool Stack<T, Allocator>::ConstIterator::operator==(const ConstIterator& other) const{
    return item == other.item;
}

template <typename T, typename Allocator>
bool Stack<T, Allocator>::ConstIterator::operator!=(const ConstIterator& other) const{
    return !(item == other.item);
}

template <typename T, typename Allocator>
const T& Stack<T, Allocator>::ConstIterator::operator*() const{
    return *item;
}

template <typename T, typename Allocator>
T* Stack<T, Allocator>::ConstIterator::operator->() const{
    return item;
}




template <typename T, typename Allocator>
typename Stack<T, Allocator>::ConstIterator& Stack<T, Allocator>::ConstIterator::operator++() {
    ++item;
    return *this;
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::ConstIterator Stack<T, Allocator>::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::ConstIterator Stack<T, Allocator>::ConstIterator::operator=(const ConstIterator& other) {
    item = other.item;
    return *this;
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::ConstIterator& Stack<T, Allocator>::ConstIterator::operator =(ConstIterator &&other) noexcept{
    item = std::move(other.item);
    return *this;
}


template <typename T, typename Allocator>
Stack<T, Allocator>::Iterator::Iterator(T* ptr) : item(ptr){}

template <typename T, typename Allocator>
Stack<T, Allocator>::Iterator::Iterator(Iterator &other) : item(other.item) {}

template <typename T, typename Allocator>
Stack<T, Allocator>::Iterator::Iterator(Iterator &&other) noexcept {
    item = std::move(other.item);
}

template <typename T, typename Allocator>
Stack<T, Allocator>::Iterator::~Iterator() = default;

template <typename T, typename Allocator>
bool Stack<T, Allocator>::Iterator::operator==(const Iterator& other) const{
    return item == other.item;
}

template <typename T, typename Allocator>
bool Stack<T, Allocator>::Iterator::operator!=(const Iterator& other) const{
    return !(item == other.item);
}

template <typename T, typename Allocator>
T& Stack<T, Allocator>::Iterator::operator*() const{
    return *item;
}

template <typename T, typename Allocator>
T* Stack<T, Allocator>::Iterator::operator->() const{
    return item;
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::Iterator& Stack<T, Allocator>::Iterator::operator++() {
    ++item;
    return *this;
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::Iterator::operator=(const Iterator& other) {
    item = other.item;
    return *this;
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::Iterator& Stack<T, Allocator>::Iterator::operator =(Iterator &&other) noexcept{
    item = std::move(other.item);
    return *this;
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::begin() const{
    return(Iterator(start_data_p));
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::end() const{
    return(Iterator(start_data_p + size));
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::ConstIterator Stack<T, Allocator>::cbegin() const{
    return(ConstIterator(start_data_p));
}

template <typename T, typename Allocator>
typename Stack<T, Allocator>::ConstIterator Stack<T, Allocator>::cend() const{
    return(ConstIterator(start_data_p + size));
}