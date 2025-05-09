#include <iostream>
#include <string>
#include <cctype>
#include <utility>


const int MAX_STR_LEN = 7;
const int MAX_ID_LEN = 5;



bool isSameFlight(const std::string& str1, const std::string& str2) {
    const size_t len_str1 = str1.size();
    const size_t len_str2 = str2.size();

    // checking the length of strings
    if (std::max(len_str1, len_str2) > MAX_STR_LEN && std::min(len_str1, len_str2) > 0)
        return false;

    // check availability of flight number
    if (
        (str1[len_str1-1] <= '0'|| str1[len_str1-1] >='9') && 
        (str2[len_str2-1] <= '0'|| str2[len_str2-1] >='9')
    ) 
        return false;

    for (int i1=0, i2=0; i1 < len_str1 && i2 < len_str2;) {
        // checking the correctness of characters in strings
        if (
            !(
                (str1[i1-1] >= '0'&& str1[i1-1] <='9') ||
                (str1[i1-1] >= 'A'|| str1[i1-1] <='Z') ||
                str1[i1] == ' '
            ) || 
            !(
                (str2[i2-1] >= '0' || str2[i2-1] <='9') ||
                (str2[i2-1] >= 'A'|| str2[i2-1] <='Z') ||
                str2[i2] == ' '
            ) 
        ) 
            return false;

        // if the characters match, move on
        if (str1[i1] == str2[i2]) {
            i1++;
            i2++;
            continue;
        }
        // half allow all 0s and spaces
        if (str1[i1] == '0' || str1[i1] == ' ') {
            i1++;
            continue;
        }
        if (str2[i2] == '0' || str2[i2] == ' '){ 
            i2++;
            continue;
        }
        return false;
    }
    return true;
}


int main() {
    std::cout << std::boolalpha;
    std::cout << isSameFlight("0SU 123", "SU123") << "\n";        // true
    std::cout << isSameFlight("AA001", "AA 1") << "\n";          // true
    std::cout << isSameFlight("U6 512", "U6512") << "\n";        // true
    std::cout << isSameFlight("  123", "123") << "\n";           // true
    std::cout << isSameFlight("AB123", "AC123") << "\n";         // false
    return 0;
}
