#include <LongNumber.h>
#include <iostream>
#include <assert.h>
int main() {
    std::cout << "Testing comaprision operators" << std::endl;
    std::cout << "123123123123" << " =? " << 123123123123ll << ": " 
              << (LongNumber("123123123123") == LongNumber(123123123123)) << std::endl;
    assert(LongNumber("123123123123") == LongNumber(123123123123));

    std::cout << "0000000123123123123" << " =? " << 123123123123ll << ": " 
              << (LongNumber("0000000123123123123") == LongNumber(123123123123)) << std::endl;
    assert(LongNumber("0000000123123123123") == LongNumber(123123123123));

    std::cout << "0000123.5436780000" << " =? " << 123.543678 << ": " 
              << (LongNumber("0000123.5436780000") ==  LongNumber(123.543678)) << std::endl;
    assert(LongNumber("0000123.5436780000") == LongNumber(123.543678));


    std::cout << "1231" << " <? " << 1231 << ": " 
              << (LongNumber("1231") < LongNumber(1231)) << std::endl;
    assert(!(LongNumber("1231") < LongNumber(1231)));

    std::cout << "-12654" << " <? " << 0 << ": " 
              << (LongNumber("-12654") < LongNumber(0)) << std::endl;
    assert(LongNumber("-12654")  < LongNumber(0));

    std::cout << "-5" << " <? " << -1.2 << ": " 
              << (LongNumber("-5") <  LongNumber(-1.2)) << std::endl;
    assert(LongNumber("-5") < LongNumber(-1.2));

    std::cout << "-0" << " != " << "+0" << ": " 
              << (LongNumber("-0") !=  LongNumber("+0")) << std::endl;
    assert(!(LongNumber("-0") != LongNumber("+0")));

    std::cout << "5" << " >? " << 1 << ": " 
              << (LongNumber("5") > LongNumber(1)) << std::endl;
    assert(LongNumber("5") > LongNumber(1));

    std::cout << 0 << " >? " << -1 << ": " 
              << (LongNumber("0") > LongNumber(-1)) << std::endl;
    assert(LongNumber("0")  > LongNumber(-1));

    std::cout << "10" << " >? " << -4 << ": " 
              << (LongNumber(10) >  LongNumber(-4)) << std::endl;
    assert(LongNumber("10") > LongNumber(-4));

    std::cout << "0.00000001" << " <=? " << 1000 << ": " 
              << (LongNumber(0.00000001) <=  LongNumber(1000)) << std::endl;
    assert(LongNumber("0.00000001") <= LongNumber(1000));


    std::cout << "0.000000001" << " >=? " << 1000 << ": " 
              << (LongNumber(0.00000001) >=  LongNumber(1000)) << std::endl;
    assert(!(LongNumber("0.00000001") >= LongNumber(1000)));
    return 0;
}