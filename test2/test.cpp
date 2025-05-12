#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <unordered_map>

#include "../test1/flighting_utils.h"



int main(){
    std::unordered_map<std::string, int> records;
    records.insert(std::make_pair("123", 123));
    records.insert(std::make_pair("123", 123));
    
    return 0;
}