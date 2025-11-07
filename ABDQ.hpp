#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : capacity_(4), size_(0), front_(0), back_(0) {
        data_ = new T[capacity_];
    }

    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0) {
        data_ = new T[capacity_];
    }

    ABDQ(const ABDQ& other) : capacity_(other.capacity_), size_(other.size_), front_(0), back_(other.size_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[(other.front_ + i) % capacity_]; 
        }
    }

    ABDQ(ABDQ&& other) noexcept : capacity_(other.capacity_), size_(other.size_), front_(other.size_), back_(other.back_) {
        data_ = other.data_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[(other.front_ + i) % capacity_]; 
        }
        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }

    ~ABDQ() {
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            size_t newCapacity_ = capacity_ * SCALE_FACTOR;
            T* newData_ = new T[newCapacity_];
            for (size_t i = 0; i < size_; i++) {
                newData_[i] = data_[(front + i) % capacity_];
            }
            delete[] data_;
            data_ = newData_;
            capacity_ = newCapacity_;
            front_ = 0;
            back_ = size_;
        }
        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            size_t newCapacity_ = capacity_ * SCALE_FACTOR;
            T* newData_ = new T[newCapacity_];
            for (size_t i = 0; i < size_; i++) {
                newData_[i] = data_[(front + i) % capacity_];
            }
            delete[] data_;
            data_ = newData_;
            capacity_ = newCapacity_;
            front_ = 0;
            back_ = size_;
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;

    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("The deque is empty");
        }
        T front = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        return front;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("The deque is empty");
        }
        back_ = (back_ + capacity_ - 1) % capacity_;
        T back = data_[back_];
        size_--;
        return back;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("The deque is empty");
        }
        return data_[front_];
    }

    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("The deque is empty");
        }
        return data_[(back_ + capacity_ -1) % capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
