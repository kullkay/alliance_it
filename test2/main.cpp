#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>


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

    throw std::invalid_argument("error in line"+input);
}


// Обрабатывает файл: удаляет неуникальные строки
void process_file(const std::string& input_filename, const std::string& output_filename) {
    std::ifstream infile(input_filename);
    if (!infile.is_open()) {
        std::cerr << "Не удалось открыть " << input_filename << std::endl;
        return;
    }

    std::unordered_map<std::string, int> line_count;
    std::vector<std::string> lines;
    std::string line;

    // Считаем количество повторений каждой строки
    while (std::getline(infile, line)) {
        ++line_count[line];
        lines.push_back(line);
    }

    infile.close();

    // Записываем только уникальные строки
    std::ofstream outfile(output_filename);
    if (!outfile.is_open()) {
        std::cerr << "Не удалось открыть " << output_filename << std::endl;
        return;
    }

    for (const auto& l : lines) {
        if (line_count[l] == 1) {
            outfile << l << '\n';
        }
    }

    outfile.close();
}

int main() {
    std::thread t1(process_file, "1_in.txt", "1_out.txt");
    std::thread t2(process_file, "2_in.txt", "2_out.txt");

    t1.join();
    t2.join();

    std::cout << "Обработка завершена." << std::endl;
    return 0;
}