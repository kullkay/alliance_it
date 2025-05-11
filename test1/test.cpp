#include <iostream>
#include <cassert>

#include "flighting_utils.h"


int pars_flighting_string_tests() {
    std::pair<std::string, int> actual;

    actual = pars_flighting_string("ABC123");
    assert(actual.first=="ABC" && actual.second==123);

    actual = pars_flighting_string("AB 123");
    assert(actual.first=="AB" && actual.second==123);

    actual = pars_flighting_string("A9 123");
    assert(actual.first=="A9" && actual.second==123);

    actual = pars_flighting_string("9A 123");
    assert(actual.first=="9A" && actual.second==123);

    try{
        actual = pars_flighting_string("AAA 123");
    } catch (std::invalid_argument& e) {
        std::string e_str = e.what();
        assert(e_str=="Format error in line: AAA 123");
    }
    return 0;
}


int isSameFlight_tests() {
    assert(isSameFlight("SUD3", "SUD003") == true);
    assert(isSameFlight("SU 123", "SU123") == true);
    assert(isSameFlight("S1 123", "S1123") == true);
    assert(isSameFlight("1U 123", "1U123") == true);
    assert(isSameFlight("123", "0123") == true);
    assert(isSameFlight("SUD3", "AUD3") == false);
    assert(isSameFlight("S2 123", "S1 123") == false);
    assert(isSameFlight("SU 1234", "SU 1235") == false);
    assert(isSameFlight("1U 123", "SU123") == false);

    try {
        isSameFlight("AAA 1", "AAA01");
    } catch (std::invalid_argument& e) {
        std::string e_str = e.what();
        assert(e_str == "In first line: Format error in line: AAA 1");
    }
    try {
        isSameFlight("AAA1", "AAA 1");
    } catch (std::invalid_argument& e) {
        std::string e_str = e.what();
        assert(e_str == "In second line: Format error in line: AAA 1");
    }
    try {
        isSameFlight("AAAAAAAAAAAAAAAA1", "AAA 1");
    } catch (std::invalid_argument& e) {
        std::string e_str = e.what();
        assert(e_str == "In second line: Format error in line: AAA 1");
    }
    return 0;
}


int main(){
    isSameFlight_tests();
}
