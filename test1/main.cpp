#include <iostream>
#include <string>
#include <cctype>
#include <utility>
#include <regex>


const int MAX_STR_LEN = 7;
const int MAX_ID_LEN = 5;


std::pair<std::string, int> extract_prefix(const std::string& input) {
    std::vector<std::regex> code_patterns = {
        std::regex(R"(^[A-Z]{3})"),
        std::regex(R"(^[A-Z]{2})"),
        std::regex(R"(^[0-9][A-Z])"),
        std::regex(R"(^[A-Z][0-9])"),
    };

    std::regex number_pattern = std::regex(R"(^ ?\d{1,5}$)");
    
    std::smatch match;
    std::string code = "";
    std::string number = "";

    for (const auto& code_pattern : code_patterns) {
        if (std::regex_search(input, match, code_pattern)) {
            
            code = match.str(0);
            number = input.substr(code.length());
            break;
        }
    }
    if (number.empty())
        number = input;

    if (std::regex_search(number, match, number_pattern)) {
        return {code, std::stoi(number)};
    }
    
    throw std::invalid_argument("Ошибка: строка не соответствует ожидаемому формату (не найдено число).");
}

bool isSameFlight(const std::string& str1, const std::string& str2) {
    const size_t len_str1 = str1.size();
    const size_t len_str2 = str2.size();

    // checking the length of strings
    if (std::max(len_str1, len_str2) > MAX_STR_LEN && std::min(len_str1, len_str2) > 0)
        return false;

    std::pair<std::string, int> result1 = extract_prefix(str1);
    std::pair<std::string, int> result2 = extract_prefix(str2);

    if (result1.first == result2.first && result1.second == result2.second)
        return true;
    
    return false;
}


int main() {
    std::cout << std::boolalpha;
    std::cout << isSameFlight("SU 123", "SU123") << "\n";        // true
    std::cout << isSameFlight("AA001", "AA 1") << "\n";          // true
    std::cout << isSameFlight("U6 512", "U6512") << "\n";        // true
    std::cout << isSameFlight("123", "123") << "\n";           // true
    std::cout << isSameFlight("AB123", "AC123") << "\n";         // false
    return 0;
}
