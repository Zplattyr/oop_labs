#pragma once
#include <iostream>
#include <cstdint>
#include <list>


template<class T>
class PoolAllocator {
    private:
        static constexpr size_t POOL_SIZE = 30000;
        T* _pool;
        std::list<T*> _free;
        size_t _free_size;
    public:

        template <class U>
        struct rebind {
            using other = PoolAllocator<U>;
        };

        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = std::size_t;

        PoolAllocator();
        PoolAllocator(PoolAllocator &&other) noexcept;

        pointer allocate();
        pointer allocate(size_type n);
        void deallocate(pointer ptr);
        void deallocate(pointer ptr, size_type n);

        PoolAllocator &operator=(PoolAllocator &&other) noexcept;

        template<typename U, typename... Args>
        void construct(U* p, Args&&... args) {
            new (p) U(std::forward<Args>(args)...);
        }
        void destroy(pointer p) {
            p->~T();
        }
};

template <typename T>
PoolAllocator<T>::PoolAllocator(){
    _pool = new T[POOL_SIZE];
    _free = std::list<T*>(POOL_SIZE);
    size_t i = 0;
    for (auto& elem : _free) {
        elem = &_pool[i++];
    }
}

template <typename T>
PoolAllocator<T>::PoolAllocator(PoolAllocator &&other) noexcept{
    _pool = std::move(other._pool);
    _free = std::move(other._free);
}

template <typename T>
PoolAllocator<T> &PoolAllocator<T>::operator=(PoolAllocator &&other) noexcept{
    _pool = std::move(other._pool);
    _free = std::move(other._free);
    return *this;
}

template <typename T>
T* PoolAllocator<T>::allocate(){
    if (_free.empty()) {
        throw std::bad_alloc();
    }
    T* tmp = _free.back();
    _free.pop_back();
    return tmp;
}

template <typename T>
T* PoolAllocator<T>::allocate(size_t n){
    if (n > _free_size) {
        throw std::logic_error("Too much to allocate");
    }
    
    if (_free.empty()) { throw std::bad_alloc(); }
    if (_free.size() < n) { throw std::bad_alloc(); }
    for (size_t i = 0; i < n - 1; ++i) {
        _free.pop_back();
    }
    T* tmp = _free.back();
    _free.pop_back();

    _free_size -= n;
    return tmp;
}

template <typename T>
void PoolAllocator<T>::deallocate(pointer ptr) {
    if (ptr < &_pool[0] || ptr > &_pool[0] + POOL_SIZE) {
        throw std::logic_error("Allocator does not own this pointer");
    }
    _free.push_back(ptr);
}

template <typename T>
void PoolAllocator<T>::deallocate(pointer ptr, size_type n) {
    if (ptr < &_pool[0] || ptr > &_pool[0] + POOL_SIZE) {
        throw std::logic_error("Allocator does not own this pointer");
    }

    if (n > POOL_SIZE - _free_size) {
        throw std::logic_error("Too much to deallocate");
    }

    T* temp = ptr;
    for (int i = 0; i < n; i++) {
        _free.push_back(temp);
        temp += sizeof(T);
    }

    _free_size += n;
}