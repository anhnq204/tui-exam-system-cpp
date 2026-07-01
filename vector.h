#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>      // size_t
#include <stdexcept>    // std::out_of_range
#include <iterator>     // std::reverse_iterator
#include <utility>      // std::move

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_cap) {
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:

    /*
    define iterators: forward & reverse
    */ 
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    Vector() : data_(nullptr), size_(0), capacity_(0) {}


    /*
    see the `explicit` wiki: https://en.cppreference.com/cpp/language/explicit
    */
    explicit Vector(size_t n) : data_(new T[n]), size_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i) data_[i] = T();
    }


    /*
    copying data from other Vector while keeping the other accessible
    see wiki: https://en.cppreference.com/cpp/language/copy_constructor
    */
    Vector(const Vector& other)
        : data_(new T[other.size_]), size_(other.size_), capacity_(other.size_) {
        for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }

    /*
    moving data from other Vector into a new Vector, dropdown the other
    see wiki: https://en.cppreference.com/cpp/language/move_constructor
    */
    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~Vector() { delete[] data_; }


    
    /*
    copy assignment operator
    see: https://en.cppreference.com/cpp/language/copy_assignment
    */
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.size_;
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
        }
        return *this;
    }

    /*
    move assignment operator
    see: https://en.cppreference.com/cpp/language/move_assignment
    */
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

    T& operator[](size_t idx) { return data_[idx]; }
    const T& operator[](size_t idx) const { return data_[idx]; }

    T& at(size_t idx) {
        if (idx >= size_) throw std::out_of_range("Vector::at");
        return data_[idx];
    }
    const T& at(size_t idx) const {
        if (idx >= size_) throw std::out_of_range("Vector::at");
        return data_[idx];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }


    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_++] = std::move(value);
    }

    void pop_back() { if (size_ > 0) --size_; }
    void clear() { size_ = 0; }

    // forward iterator
    iterator begin() { return data_; }
    iterator end() { return data_ + size_; }
    const_iterator begin() const { return data_; }
    const_iterator end() const { return data_ + size_; }
    const_iterator cbegin() const { return data_; }
    const_iterator cend() const { return data_ + size_; }

    // reverse iterator
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }
};

#endif