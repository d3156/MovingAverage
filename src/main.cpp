#include "move_average_interface.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

#define FAIL(isok, str) \
if (isok) std::cout << "\033[1;32m[TEST SUCCESS]\033[0m " << str << "\n"; \
else std::cout << "\033[1;31m[TEST FAILED]\033[0m " << str << "\n"



const int window_sizes[6] = { 4, 8, 16, 32, 64, 128 };

///
/// Простой тест скользящего среднего
/// Размер окна равен 3
/// Количество данных 10
///
template <typename Floating>
bool simpleTest()
{
    SimpleMoveAverage<Floating> sma_calc(3);
    constexpr Floating EPS = 0.00001f;
    const Floating expect_res[8] = {90.18666f, 89.73000f, 89.52333f, 89.47333f, 89.26333f, 88.82000f, 88.28666f, 88.05666f};
    const Floating test_data[10] = {90.66f, 90.23f, 89.67f, 89.29f, 89.61f, 89.52f, 88.66f, 88.28f, 87.92f, 87.97f};
    std::vector<Floating> res;
    res.reserve(8);
    for (auto i : test_data) {
       sma_calc.next(i) ;
       if (sma_calc.hasCurrent()) res.push_back(sma_calc.current());
    }
    for (int i = 0; i < 8; i++)
       if (res[i] - expect_res[i] > EPS) {
           std::cout << "[Test failed] : " << std::setprecision(8) << res[i] << "!=" << std::setprecision(8) << expect_res[i] << "\n";
           return false;
       }
    return true;
}

bool loadTesting(size_t max_size = 1e6)
{

}

int main()
{
    FAIL(simpleTest<float>(), "Simple test on float");
    FAIL(simpleTest<double>(), "Simple test on double");
    // for (auto i = 0; i < DATA_LENGTH; i++)
    // {

    // }

    // for (auto i : window_sizes) {

    // }

    return 0;
}