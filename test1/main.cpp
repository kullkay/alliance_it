#include <iostream>

#include "flighting_utils.h"


int main() {
    std::cout << std::boolalpha;
    std::cout << isSameFlight("SU 123", "SU123") << "\n";        // true
    std::cout << isSameFlight("SUD123", "SUD0123") << "\n";        // true
    std::cout << isSameFlight("AA001", "AA 1") << "\n";          // true
    std::cout << isSameFlight("U6 512", "U6512") << "\n";        // true
    std::cout << isSameFlight("123", "123") << "\n";           // true
    std::cout << isSameFlight("AB123", "AC123") << "\n";         // false
    std::cout << isSameFlight("SUD 123", "SU123") << "\n";        // error
    return 0;
}
