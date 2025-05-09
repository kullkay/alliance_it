#include <iostream>
#include <regex>
#include <string>
#include <cctype>


std::pair<std::string, int> extract_prefix(const std::string& input) {
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
            code = match.str(0);
            number = input.substr(code.length());
            break;
        }
    }

    
    if (std::regex_search(number, match, number_pattern)) {
        return {code, std::stoi(number)};
    }
    
    throw std::invalid_argument("Ошибка: строка не соответствует ожидаемому формату (не найдено число).");
}

int main() {
    std::vector<std::string> test_cases = {
        "AB12345",
        "ABCxyz",
        "A1 text",
        "12 text",
        "AA text",
        "AB text more",
        "X9 something",
        "something else"
    };

    for (const auto& test : test_cases) {
        auto [prefix, rest] = extract_prefix(test);
        std::cout << "Вход:       [" << test << "]\n";
        std::cout << "Совпадение: [" << prefix << "]\n";
        std::cout << "Остальное:  [" << rest << "]\n\n";
    }

    return 0;
}