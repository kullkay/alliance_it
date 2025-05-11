#include <iostream>
#include <string>
#include <cctype>
#include <utility>
#include <regex>
#include "flighting_utils.h"


const int MAX_STR_LEN = 7;
const int MAX_ID_LEN = 5;


std::pair<std::string, int> pars_flighting_string(const std::string& input) {
    std::vector<std::regex> code_patterns = {
        std::regex(R"(^[A-Z]{3})"),
        std::regex(R"(^[A-Z]{2} ?)"),
        std::regex(R"(^[0-9][A-Z] ?)"),
        std::regex(R"(^[A-Z][0-9] ?)"),
    };

    std::regex number_pattern = std::regex(R"(^\d{1,5}$)");
    
    std::smatch match;
    std::string code = "";
    std::string number = "";

    for (const auto& code_pattern : code_patterns) {
        if (std::regex_search(input, match, code_pattern)) {
            int code_size = match.str(0).size();
            if (match.str(0)[code_size-1] == ' ')
                code = match.str(0).substr(0, code_size-1);
            else
                code = match.str(0);

            number = input.substr(code_size);
            break;
        }
    }
    if (number.empty())
        number = input;

    if (std::regex_search(number, match, number_pattern)) {
        return {code, std::stoi(number)};
    }
    
    throw std::invalid_argument("format error in line: "+input);
}


bool isSameFlight(const std::string& str1, const std::string& str2) {
    const size_t len_str1 = str1.size();
    const size_t len_str2 = str2.size();

    
    if (std::max(len_str1, len_str2) > MAX_STR_LEN && std::min(len_str1, len_str2) > 0)
        return false;

    std::pair<std::string, int> result1;
    std::pair<std::string, int> result2;
    try {
        result1 = pars_flighting_string(str1);
    } catch (std::invalid_argument& error) {
        std::string e_str = error.what();
        throw std::invalid_argument("In first line: "+e_str);
    }

    try {
        result2 = pars_flighting_string(str2);
    } catch (std::invalid_argument& error) {
        std::string e_str = error.what();
        throw std::invalid_argument("In second line: "+e_str);
    }

    if (result1.first == result2.first && result1.second == result2.second)
        return true;
    return false;
}
