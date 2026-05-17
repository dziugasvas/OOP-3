#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include <algorithm>
#include <iterator>

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

    using iterator = T*;
    using const_iterator = const T*;

    Vector() { ReAlloc(2); }

    ~Vector() { delete[] data_; }

    Vector(const Vector& other) {
        ReAlloc(other.capacity_);
        size_ = other.size_;
        for (size_t i = 0; i < size_; i++)
            data_[i] = other.data_[i];
    }

    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            ReAlloc(other.capacity_);
            size_ = other.size_;
            for (size_t i = 0; i < size_; i++)
                data_[i] = other.data_[i];
        }
        return *this;
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    size_t max_size() const { return size_t(-1) / sizeof(T); }

    void push_back(const T& value) {
        if (size_ >= capacity_)
            ReAlloc(capacity_ * 2);
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_)
            ReAlloc(capacity_ * 2);
        data_[size_++] = std::move(value);
    }

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }

    void clear() noexcept { size_ = 0; }
    
    void resize(size_t newSize) {
        if (newSize > capacity_)
            ReAlloc(newSize);
        if (newSize > size_)
            for (size_t i = size_; i < newSize; i++)
                data_[i] = T{};
        size_ = newSize;
    }

    void assign(size_t count, const T& value) {
        clear();
        for (size_t i = 0; i < count; i++)
            push_back(value);
    }
};

#endif