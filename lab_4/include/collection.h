#pragma once

#include <string>
#include <iostream>
#include <memory>

template <typename T>
class Collection {
public:
    Collection();
    Collection(size_t n);
    virtual ~Collection();
    
    Collection(const Collection &other);
    Collection(Collection &&other) noexcept;
    Collection<T>& operator=(const Collection<T>& other);
    Collection<T>& operator=(Collection<T>&& other) noexcept;

    void displayGCenters() const;
    void displayAreas() const;
    double getAllArea() const;

    T* begin();
    T* end();

    T& operator[](size_t index) const;
    size_t getSize() const;
    void remove(size_t index);
    void pushBack(T& elem);

    template <typename _T>
    friend std::ostream& operator<<(std::ostream &stream, const Collection<_T>&  collection);

private:
    std::unique_ptr<T[]> elems;
    size_t capacity;
    size_t size;
};

#include "collection.hpp"