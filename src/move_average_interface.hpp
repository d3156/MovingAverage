#pragma once
#include <queue>
#include <stdexcept>
#include <vcruntime.h>

template <typename Floating> class SimpleMoveAverage {
public:
    SimpleMoveAverage(size_t k) : k_(k) {}

    void next(Floating next) {
        fifo_.push(next);
        sma_ += next / k_; /// Накапливаем сумму, пока не достигнем размера окна
        if (fifo_.size() == k_) hasSma_ = true;
        if (fifo_.size() > k_) { // Когда превысили размера окна - вынимаем последний элемент из суммы
            sma_ -= fifo_.front() / (Floating)k_;
            fifo_.pop();
        }
    }

    size_t getK() { return k_; }

    bool hasCurrent() { return hasSma_; }

    Floating current() {
        if (!hasSma_) throw std::invalid_argument("[ERROR] SMA hasn't calculated yet!");
        return sma_;
    }

private:
    size_t k_ = 0;
    Floating sma_ = 0;
    bool hasSma_ = false;
    std::queue<Floating> fifo_;
};