#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <algorithm>

template <typename T>
class Vector {
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void ReAlloc(size_t newCapacity) {
        T* newBlock = new T[newCapacity];
        if (newCapacity < size_)
            size_ = newCapacity;
        for (size_t i = 0; i < size_; i++)
            newBlock[i] = std::move(data_[i]);
        delete[] data_;
        data_ = newBlock;
        capacity_ = newCapacity;
    }

public:
    Vector() { ReAlloc(2); }

    ~Vector() { delete[] data_; }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    void push_back(const T& value) {
        if (size_ >= capacity_)
            ReAlloc(capacity_ * 2);
        data_[size_] = value;
        size_++;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_)
            ReAlloc(capacity_ * 2);
        data_[size_] = std::move(value);
        size_++;
    }
};

#endif