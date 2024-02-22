#include <LongNumber.h>
#include <iostream>
#include <cassert>

int main() {
    std::cout << "Testing aritmetic (and a bit more)" << std::endl;

    std::cout << "to_string(+510924519248542.11234710836823523)" << ": " "Get :"
              << LongNumber("+510924519248542.11234710836823523").to_string() <<  " ; Right answer: " << "510924519248542.11234710836823523" << std::endl;
    assert(LongNumber("+510924519248542.11234710836823523").to_string() == "510924519248542.11234710836823523");


    std::cout << 1 << " +? " << 2 << ": " << "Get :"
              << (LongNumber(1) + LongNumber(2)) <<  " ; Right answer: " << LongNumber(3) << std::endl;
    assert(LongNumber(1) + LongNumber(2) == LongNumber(3));
    std::cout << 1.00001 << " +? " << 0.99999 << ": " << "Get :"
              << (LongNumber(1.00001) + LongNumber(0.99999)) <<  " ; Right answer: " << LongNumber(2) << std::endl;
    assert(LongNumber(1.00001) + LongNumber(0.99999) == LongNumber(2));
    
    std::cout << 2 << " +? " << -1 << ": " << "Get :"
              << (LongNumber(2) + LongNumber(-1)) <<  " ; Right answer: " << LongNumber(1) << std::endl;
    assert(LongNumber(2) + LongNumber(-1) == LongNumber(1));

    std::cout << "123.412323" << " +? " << "784531235.19947436" << ": " << "Get :"
              << (LongNumber("123.412323") + LongNumber("784531235.19947436")) <<  " ; Right answer: " << LongNumber("784531358.61179736") << std::endl;
    assert(LongNumber("123.412323") + LongNumber("784531235.19947436") == LongNumber("784531358.61179736"));


    std::cout << 1 << " -? " << 2 << ": " << "Get :"
              << (LongNumber(1) - LongNumber(2)) <<  " ; Right answer: " << LongNumber(-1) << std::endl;
    assert(LongNumber(1) - LongNumber(2) == LongNumber(-1));
    std::cout << -1 << " -? " << 2 << ": " << "Get :"
              << (LongNumber(-1) - LongNumber(2)) <<  " ; Right answer: " << LongNumber(-3) << std::endl;
    assert(LongNumber(-1) - LongNumber(2) == LongNumber(-3));
    
    std::cout << 100 << " -? " << 2 << ": " << "Get :"
              << (LongNumber(100) - LongNumber(2)) <<  " ; Right answer: " << LongNumber(98) << std::endl;
    assert(LongNumber(100) - LongNumber(2) == LongNumber(98));

    std::cout << "239587" << " -? " << "982351" << ": " << "Get :"
              << (LongNumber("239587") - LongNumber("982351")) <<  " ; Right answer: " << LongNumber("-742764") << std::endl;
    assert(LongNumber("239587") - LongNumber("982351") == LongNumber("-742764"));

    std::cout << 100 << " -? " << 2 << ": " << "Get :"
              << (LongNumber(100) - LongNumber(2)) <<  " ; Right answer: " << LongNumber(98) << std::endl;
    assert(LongNumber(100) - LongNumber(2) == LongNumber(98));

    std::cout << 2 << " *? " << 12 << ": " << "Get :"
              << (LongNumber(2) * LongNumber(12)) <<  " ; Right answer: " << LongNumber(24) << std::endl;
    assert(LongNumber(2) * LongNumber(12) == LongNumber(24));

    std::cout << 0.0001 << " *? " << 0.0001 << ": " << "Get :"
              << (LongNumber(0.0001) * LongNumber(0.0001)) <<  " ; Right answer: " << LongNumber("0.00000001") << std::endl;
    assert(LongNumber(0.0001) * LongNumber(0.0001) == LongNumber("0.00000001"));

    std::cout << 4 << " *? " << 0.5 << ": " << "Get :"
              << (LongNumber(4) * LongNumber(0.5)) <<  " ; Right answer: " << LongNumber(2) << std::endl;
    assert(LongNumber(4) * LongNumber(0.5) == LongNumber(2));

    std::cout << "209856198034" << " *? " << "-4167013452" << ": " << "Get :"
              << (LongNumber("209856198034") * LongNumber("-4167013452")) <<  " ; Right answer: " << LongNumber("-874473600193253953368") << std::endl;
    assert(LongNumber("209856198034") * LongNumber("-4167013452") == LongNumber("-874473600193253953368"));

    std::cout << 1 << " /? " << 2 << ": " << "Get :"
              << (LongNumber(1) / LongNumber(2)) <<  " ; Right answer: " << LongNumber(0.5) << std::endl;
    assert(LongNumber(1) / LongNumber(2) == LongNumber(0.5));

    std::cout << 0.1 << " /? " << 50 << ": " << "Get :"
              << (LongNumber(0.1)  / LongNumber(50)) <<  " ; Right answer: " << LongNumber(0.002) << std::endl;
    assert(LongNumber(0.1) / LongNumber(50) == LongNumber(0.002));

    std::cout << -6 << " /? " << 3 << ": " << "Get :"
              << (LongNumber(-6) / LongNumber(3)) <<  " ; Right answer: " << LongNumber(-2) << std::endl;
    assert(LongNumber(-6) / LongNumber(3) == LongNumber(-2));

    std::cout << "8912468648" << " /? " << "1202156.25" << ": " << "Get :"
              << (LongNumber(8912468648) / LongNumber(1202156.25)).to_string(12) <<  " ; Right answer: " << LongNumber("7413.735650419818") << std::endl;
    assert((LongNumber(8912468648) / LongNumber(1202156.25)).to_string(12) == LongNumber("7413.735650419818"));


    return 0;
}