#pragma once
#include <queue>
#include <stdexcept>

///
/// Класс для расчета простого скользящего среднего 
/// Накапливает значения до тех пор, пока не небертся достаточное кол-во для расчета скользящего среднего
/// С помощью hasCurrent можно определить, рассчитано ли значение
///
template <typename Floating> class SimpleMoveAverage {
public:
    
    SimpleMoveAverage(size_t k) : k_(k) {}

    ///
    /// Задать следющее значение величины для расчета
    ///
    void next(Floating next) {
        fifo_.push(next);
        sma_ += next / k_; /// Накапливаем сумму, пока не достигнем размера окна
        if (fifo_.size() == k_) hasSma_ = true;
        if (fifo_.size() > k_) { // Когда превысили размера окна - вынимаем последний элемент из суммы
            sma_ -= fifo_.front() / (Floating)k_;
            fifo_.pop();
        }
    }

    ///
    /// Заданный размер окна для расчета
    ///
    size_t getK() { return k_; }

    ///
    /// Признак наличия расчитанного значения скользящего среднего
    ///
    bool hasCurrent() { return hasSma_; }

    ///
    /// Последнее расчитанное значение скользящего среднего
    /// Выдаст исключение при попытке получить значение до того, как оно будет расчитано.
    ///
    Floating current() {
        if (!hasSma_) throw std::invalid_argument("[ERROR] SMA hasn't calculated yet!");
        return sma_;
    }

private:
    size_t k_ = 0;                /// Размер окна расчета
    Floating sma_ = 0;            /// Предыдущее расчитанное значение
    bool hasSma_ = false;         /// Признак наличия расчитанного значения
    std::queue<Floating> fifo_;   /// Очередь для быстрого расчета следующего значения
};