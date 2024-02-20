#include <LongNumber.h>
#include <iostream>
int main() {
    LongNumber a(std::string("1123.123"));
    LongNumber b(std::string("1"));
    std::cout << "Hello" << '\n' << (a + b).t_string();
    std::cout << "Hello" << '\n' << (b).t_string();
    return 0;
}