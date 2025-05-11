#include <cassert>
#include <iostream>
#include "flighting_utils.h"


int main() {
    assert(isSameFlight("SUD3", "SUD003") == true);
    assert(isSameFlight("SU 123", "SU123") == true);
    assert(isSameFlight("S1 123", "S1123") == true);
    assert(isSameFlight("1U 123", "1U123") == true);
    assert(isSameFlight("SUD3", "AUD3") == false);
    assert(isSameFlight("S2 123", "S1 123") == false);
    assert(isSameFlight("SU 1234", "SU 1235") == false);
    assert(isSameFlight("1U 123", "SU123") == false);

    try {
        isSameFlight("AAA 1", "AAA01");
    } catch (std::invalid_argument& e) {
        std::string e_str = e.what();
        assert(e_str == "In first line: format error in line: AAA 1");
    }
    try {
        isSameFlight("AAA1", "AAA 1");
    } catch (std::invalid_argument& e) {
        std::string e_str = e.what();
        assert(e_str == "In second line: format error in line: AAA 1");
    }
    try {
        isSameFlight("AAAAAAAAAAAAAAAA1", "AAA 1");
    } catch (std::invalid_argument& e) {
        std::string e_str = e.what();
        assert(e_str == "In second line: format error in line: AAA 1");
    }
    return 0;
}