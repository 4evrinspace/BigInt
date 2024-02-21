#include <LongNumber.h>
#include <iostream>
#include <chrono>
int main() {
    const auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << LongNumber::calculate_pi(700);
    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << std::endl << int_ms.count();
    return 0;
}

