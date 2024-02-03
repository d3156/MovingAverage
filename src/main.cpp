#include "move_average.hpp"
#include <iomanip>
#include <iostream>
#include <ratio>
#include <vector>
#include <random>
#include <chrono>

///
/// Простой тест скользящего среднего
/// Размер окна равен 3
/// Количество данных 10
///
template <typename Floating> bool simpleTest() {
    SimpleMoveAverage<Floating> sma_calc(3);
    constexpr Floating EPS = 0.00001f;
    const Floating expect_res[8] = {90.18666f, 89.73000f, 89.52333f, 89.47333f, 89.26333f, 88.82000f, 88.28666f, 88.05666f};
    const Floating test_data[10] = {90.66f, 90.23f, 89.67f, 89.29f, 89.61f, 89.52f, 88.66f, 88.28f, 87.92f, 87.97f};
    std::vector<Floating> res;
    res.reserve(8);
    for (auto i : test_data) {
        sma_calc.next(i);
        if (sma_calc.hasCurrent()) res.push_back(sma_calc.current());
    }
    for (int i = 0; i < 8; i++)
        if (res[i] - expect_res[i] > EPS) {
            std::cout << "[Test failed] : " << std::setprecision(8) << res[i] << "!=" << std::setprecision(8) << expect_res[i] << "\n";
            return false;
        }
    return true;
}

template <typename Floating> 
bool loadTesting(size_t max_size = 1e6) {
    bool isfloat = typeid(Floating) == typeid(float); // evaluates to true
    SimpleMoveAverage<Floating> calcs[] = {4, 8, 16, 32, 64, 128};
    for (SimpleMoveAverage<Floating> &i : calcs) {
        std::mt19937 gen(12345); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<Floating> distr;
        int count = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < max_size; j++) {
            i.next(distr(gen));
            if (i.hasCurrent()) count++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "\033[1;32m[TEST SPEED]\033[0m For " << ((isfloat) ? "float" : "double") << " and k = " << i.getK()
                  << ", speed = " << (double)count / (duration.count() * 1000) << " calc/sec\n";
    }
    return true;
}

#define FAIL(isok, str)                                                                                                                              \
    if (isok)                                                                                                                                        \
        std::cout << "\033[1;32m[TEST SUCCESS]\033[0m " << str << "\n";                                                                              \
    else                                                                                                                                             \
        std::cout << "\033[1;31m[TEST FAILED]\033[0m " << str << "\n"

int main() {
    FAIL(simpleTest<float>(), "Simple test on float");
    FAIL(simpleTest<double>(), "Simple test on double");
    FAIL(loadTesting<float>(), "Load Testing on float");
    FAIL(loadTesting<double>(), "Load Testing on double");
    return 0;
}