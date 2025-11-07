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

    ABDQ(const ABDQ& other) : capacity_(other.capacity_), size_(other.size_), front_(0), back_(other.back_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[]; 
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
            data_[i] = other.data_[i];
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
            size_t newCapacity_ = capacity_ * 2;
            T* newData_ = new T[newCapacity_];
            for (size_t i = 0; i < size_; i++) {
                newData_[i] = data_[i];
            }
            delete[] data_;
            data_ = newData_;
            capacity_ = newCapacity_;
        }
        data_[size_++] = item;
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
        
        }
        data_[back_] = item;
        
    }

    // Deletion
    T popFront() override {
        T front = data_[front_];
        if (front == capacity_-1) {
            back_ = 0;
        }
        else {
            front_++;
        }
        size_--;
        return front;
    }
    T popBack() override {
        T back = data_[back_];
        if (back_ == 0) {
            back_ = capacity_ - 1;
        }
        else {
            back_--;
        }
        size_--;
        return back;
    }

    // Access
    const T& front() const override {
        return data_[front_];
    }

    const T& back() const override {
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
