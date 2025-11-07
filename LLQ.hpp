#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        if (!list.getHead()) {
            throw std::runtime_error("The queue is empty");
        }
        T data = list.getHead()->data;
        list.removeHead();
        return data;
    }

    // Access
    T peek() const override {
        if (!list.getHead()) {
            throw std::runtime_error("The queue is empty");
        }
        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

};