#include "collection.h"
template <typename T>
Collection<T>::Collection() : size(0), capacity(2) {
    elems = std::make_unique<T[]>(capacity);
}
template <typename T>
Collection<T>::Collection(size_t n) : size(n), capacity(n*2) {
    elems = std::make_unique<T[]>(capacity);
}
template <typename T>
Collection<T>::~Collection() {
    size = 0;
    capacity = 0;
}
template <typename T>
Collection<T>::Collection(Collection<T> &&other) noexcept {
    size = other.size;
    capacity = other.capacity;
    elems = std::move(other.data);
}
template <typename T>
Collection<T>::Collection(const Collection<T> &other) {
    size = other.size;
    capacity = other.capacity;
    elems = std::make_unique<T[]>(capacity);
    for (int i = 0; i < other.size; i++) {
        elems[i] = other[i];
    }
}
template <typename T>
Collection<T>& Collection<T>::operator=(const Collection<T>& other)
{
    size = other.size;
    capacity = other.capacity;
    elems = std::make_unique<T[]>(capacity);
    for (int i = 0; i < other.size(); i++) {
        elems[i] = other[i];
    }
    return *this;
}
template <typename T>
Collection<T>& Collection<T>::operator=(Collection<T>&& other) noexcept
{
    size = other.size;
    capacity = other.capacity;
    elems = std::move(other.elems);
    return *this;
}
template <typename T>
T* Collection<T>::begin() {
        return elems.get();
}
template <typename T>
T* Collection<T>::end() {
        return elems.get() + size;
}
template <typename T>
T& Collection<T>::operator[](size_t index) const {
    if (index >= size) {
        std::cout << size << std::endl;
        throw std::out_of_range("Index out of range");
    }
    return elems[index];
}
template <typename T>
size_t Collection<T>::getSize() const {
    return size;
}
template <typename T>
void Collection<T>::pushBack(T& elem)  {
    if (size >= capacity) {
        capacity *= 2;
        std::unique_ptr<T[]> newCollection = std::make_unique<T[]>(capacity);
        for (int i = 0; i < size; i++) {
            newCollection[i] = this->elems[i];
        }
        this->elems = std::move(newCollection);
    }
    this->elems[size++] = elem;
}
template <typename T>
std::ostream& operator<<(std::ostream& out, const Collection<T>& _this) //out overload
{
    for (size_t i = 0; i < _this.size; ++i) {
        out << "\n      V " << _this.elems[i]->getTag() << " V" << "\n" << *_this.elems[i];
    }
    return out;
}
template <typename T>
void Collection<T>::displayGCenters() const{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << "\n   V " << this->elems[i]->getTag() << " CENTER V" << "\n" ;
        std::cout << elems[i]->getGCenter();
    }
}
template <typename T>
void Collection<T>::displayAreas() const{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << this->elems[i]->getTag() << " AREA = " << double(*elems[i]) << std::endl;
    }
}
template <typename T>
double Collection<T>::getAllArea() const{
    double result = 0;
    for (size_t i = 0; i < size; i++)
    {
        result += double(*elems[i]);
    }
    return result;
}
template <typename T>
void Collection<T>::remove(size_t index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    this->elems[index] = T();
    for (int i = index; i < size - 1; ++i)
    {
        this->elems[i] = this->elems[i + 1];
    }
    
    size--;
}