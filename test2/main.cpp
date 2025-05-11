#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <set>
#include "flighting_utils.h"


struct FlightingRecords {
    protected:
        std::set<std::pair<std::string, int>> _unique_records;
        std::mutex _mtx;
    public:
        bool add_records(std::pair<std::string, int> record) {
            std::lock_guard<std::mutex> guard(_mtx);
            int len = _unique_records.size();
            _unique_records.insert({record.first, record.second});
            if (len==_unique_records.size()) 
                return false;
            return true;
        }
};


void process_file(
    const std::string& input_filename,
    const std::string& output_filename,
    FlightingRecords& db
) {
    std::ifstream infile(input_filename);
    std::ofstream outfile(output_filename);

    if (!infile.is_open()) {
        std::cerr << "Failed open file: " << input_filename << std::endl;
        return;
    }
    if (!outfile.is_open()) {
        std::cerr << "Failed open file: " << output_filename << std::endl;
        return;
    }

    std::string record;
    std::getline(infile, record);

    if (db.add_records(pars_flighting_string(record)))
        outfile<<record<<'\n';

    infile.close();
    outfile.close();
}


int main() {
    FlightingRecords db;
    std::thread t1(process_file, "1_in.txt", "1_out.txt", std::ref(db));
    std::thread t2(process_file, "2_in.txt", "2_out.txt", std::ref(db));

    t1.join();
    t2.join();

    std::cout << "Обработка завершена." << std::endl;
    return 0;
}