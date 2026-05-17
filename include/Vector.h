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

    Vector() {}

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
            T* newBlock = other.capacity_ == 0 ? nullptr : new T[other.capacity_];
            for (size_t i = 0; i < other.size_; i++)
                newBlock[i] = other.data_[i];
            delete[] data_;
            data_ = newBlock;
            capacity_ = other.capacity_;
            size_ = other.size_;
        }
        return *this;
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    size_t max_size() const { return size_t(-1) / sizeof(T); }

    void push_back(const T& value) {
    if (size_ >= capacity_)
        ReAlloc(capacity_ == 0 ? 1 : capacity_ * 2);
    data_[size_++] = value;
    }

    void push_back(T&& value) {
    if (size_ >= capacity_)
        ReAlloc(capacity_ == 0 ? 1 : capacity_ * 2);
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

    T& operator[](size_t pos) { return data_[pos]; }
    const T& operator[](size_t pos) const { return data_[pos]; }
    
    T* data() { return data_; }
    const T* data() const { return data_; }

    T& at(size_t pos) {
        if (pos >= size_)
            throw std::out_of_range("Vector::at - indeksas uz ribu");
        return data_[pos];
    }
    const T& at(size_t pos) const {
        if (pos >= size_)
            throw std::out_of_range("Vector::at - indeksas uz ribu");
        return data_[pos];
    }

    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }

    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }

    void pop_back() {
        if (size_ > 0)
            size_--;
    }

    void shrink_to_fit() {
        if (capacity_ > size_)
            ReAlloc(size_);
    }

    void reserve(size_t newCapacity) {
        if (newCapacity > capacity_)
            ReAlloc(newCapacity);
    }

    iterator insert(const_iterator pos, const T& value) {
        size_t idx = data_ == nullptr ? 0 : pos - data_;
        if (size_ >= capacity_)
            ReAlloc(capacity_ == 0 ? 1 : capacity_ * 2);
        for (size_t i = size_; i > idx; i--)
            data_[i] = std::move(data_[i - 1]);
        data_[idx] = value;
        size_++;
        return data_ + idx;
    }

    iterator erase(const_iterator pos) {
        size_t idx = pos - data_;
        for (size_t i = idx; i < size_ - 1; i++)
            data_[i] = std::move(data_[i + 1]);
        size_--;
        return data_ + idx;
    }

    iterator erase(const_iterator first, const_iterator last) {
        size_t idxF  = first - data_;
        size_t count = last - first;
        for (size_t i = idxF; i + count < size_; i++)
            data_[i] = std::move(data_[i + count]);
        size_ -= count;
        return data_ + idxF;
    }

    void swap(Vector& other) noexcept {
        std::swap(data_,     other.data_);
        std::swap(size_,     other.size_);
        std::swap(capacity_, other.capacity_);
    }

    template <typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_t idx = data_ == nullptr ? 0 : pos - data_;
        size_t count = std::distance(first, last);
        if (count == 0)
            return data_ + idx;
        if (size_ + count > capacity_)
            ReAlloc((size_ + count) * 2);
        for (size_t i = size_ + count - 1; i >= idx + count; i--)
            data_[i] = std::move(data_[i - count]);
        size_t j = idx;
        for (auto it = first; it != last; ++it, ++j)
            data_[j] = *it;
        size_ += count;
        return data_ + idx;
    }
    
};

template <typename T>
bool operator==(const Vector<T>& a, const Vector<T>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i]) return false;
    return true;
}

template <typename T>
bool operator!=(const Vector<T>& a, const Vector<T>& b) { return !(a == b); }

template <typename T>
bool operator<(const Vector<T>& a, const Vector<T>& b) {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template <typename T>
bool operator>(const Vector<T>& a, const Vector<T>& b) { return b < a; }

template <typename T>
bool operator<=(const Vector<T>& a, const Vector<T>& b) { return !(b < a); }

template <typename T>
bool operator>=(const Vector<T>& a, const Vector<T>& b) { return !(a < b); }

template <typename T>
void swap(Vector<T>& a, Vector<T>& b) noexcept { a.swap(b); }

#endif
