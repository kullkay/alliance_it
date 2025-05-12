#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <map>

#include "../test1/flighting_utils.h"


struct FlightingRecord {
    std::string outfile_name;
    std::string record_str;
    bool unique = true;
};


struct DBFlightingRecords {
    protected:
        std::mutex _mtx;
    public:
        std::map<std::pair<std::string, int>, FlightingRecord> records;
        bool add_records(FlightingRecord& record) {
            std::lock_guard<std::mutex> guard(_mtx);
            std::pair<std::string, int> record_key = pars_flighting_string(record.record_str);
            auto old_record = records.find(record_key);
            if (old_record != records.end()) {
                old_record->second.unique = false;
                return false;
            }

            records.insert(std::make_pair (record_key, record));
            return true;
        }
};


void output_unique_record (
    const std::string& output_filename,
    DBFlightingRecords& db
) {
    std::ofstream outfile(output_filename);
    if (!outfile.is_open()) {
        std::cerr << "Failed open file: " << output_filename << std::endl;
        return;
    }

    for (auto record = db.records.cbegin(); record != db.records.cend(); record++) {
        if (record->second.outfile_name == output_filename && record->second.unique)
            outfile << record->second.record_str <<'\n';
    }
    outfile.close();
}


void parsing_flighting_file(
    const std::string& input_filename,
    const std::string& output_filename,
    DBFlightingRecords& db
) {
    std::ifstream infile(input_filename);

    if (!infile.is_open()) {
        std::cerr << "Failed open file: " << input_filename << std::endl;
        return;
    }

    std::string record_str;
    while (std::getline(infile, record_str)) {
        FlightingRecord record;
        record.outfile_name=output_filename;
        record.record_str = record_str;
        db.add_records(record);
    }

    infile.close();

    std::ofstream outfile(output_filename);
    if (!outfile.is_open()) {
        std::cerr << "Failed open file: " << output_filename << std::endl;
        return;
    }

    for (auto record = db.records.cbegin(); record != db.records.cend(); record++) {
        if (record->second.outfile_name == output_filename && record->second.unique)
            outfile << record->second.record_str << " " << record->second.unique <<'\n';
    }
    outfile.close();
}


int main() {
    DBFlightingRecords db;
    std::thread t_in1(parsing_flighting_file, "1_in.txt", "1_out.txt", std::ref(db));
    std::thread t_in2(parsing_flighting_file, "2_in.txt", "2_out.txt", std::ref(db));

    t_in1.join();
    t_in2.join();

    std::thread t_out1(output_unique_record, "1_out.txt", std::ref(db));
    std::thread t_out2(output_unique_record, "2_out.txt", std::ref(db));

    t_out1.join();
    t_out2.join();

    std::cout << "Обработка завершена." << std::endl;
    return 0;
}
