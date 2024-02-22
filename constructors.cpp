#include <LongNumber.h>
#include <iostream>
#include <assert.h>
int main() {
    std::cout << "Testing if all constructors are equal (to string constructor)" << std::endl;
    LongNumber state = std::string("123.45678");
    std::cout << state << std::endl;
    std::cout << "from double: " << LongNumber(123.45678) << std::endl;
    assert(state == LongNumber(123.45678));
    std::cout << "from string literal: " << "123.45678"_Ln << std::endl;
    assert(state == "123.45678"_Ln);
    std::cout << "from double literal: " << 123.45678_Ln << std::endl;
    assert(state == 123.45678_Ln);

    state = std::string("123");
    std::cout << "from int: " << LongNumber(123) << std::endl;
    assert(state == LongNumber(123));
    std::cout << "from string literal: " << "123"_Ln << std::endl;
    assert(state == 123_Ln);
    std::cout << "from int literal: " << 123_Ln << std::endl;
    assert(state == 123_Ln);
    return 0;
}