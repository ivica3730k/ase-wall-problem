#include <iostream>
#include <string>
#include <map>
#include <list>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std::chrono;


//#define PRINT_OUT
using STORAGE_STRUCTURE = std::map<std::string, std::string>;

int main(int argc, char *argv[]) {
    STORAGE_STRUCTURE north_key_south_value;
    STORAGE_STRUCTURE south_key_north_value;

    // Load data into memory
    auto load_data_start = high_resolution_clock::now();
    std::ifstream file(argv[1]);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) {
                break;
            }
            std::stringstream ss(line);
            std::string north;
            getline(ss, north, ',');
            std::string south;
            getline(ss, south, ',');
            //north_key_south_value[north] = south;
            //south_key_north_value[south] = north;
            north_key_south_value.insert(std::pair<std::string,std::string>(north,south));
            south_key_north_value.insert(std::pair<std::string,std::string>(south,north));
        }
    } else {
        std::cout << "Unable to read results file: " << argv[1] << std::endl;
        return 1;
    }
    auto load_data_end = high_resolution_clock::now();


    std::list<std::string> results_sequence;
    results_sequence.push_back(north_key_south_value.begin()->first);
    results_sequence.push_back(north_key_south_value.begin()->second);

    while (true) {
        // search for southern symbol in via northern symbol
        try {
            std::string south_side_symbol = results_sequence.back();
            results_sequence.push_back(north_key_south_value.at(south_side_symbol));
        }
        catch (std::out_of_range &e) {
            break;
        }
    }

    while (true) {
        // search for southern symbol in via northern symbol
        try {
            std::string north_side_symbol = results_sequence.front();
            results_sequence.push_front(south_key_north_value.at(north_side_symbol));
        }
        catch (std::out_of_range &e) {
            break;
        }
    }
    auto processing_end = high_resolution_clock::now();
    auto data_load_duration = duration_cast<microseconds>(load_data_end - load_data_start);
    auto processing_duration = duration_cast<microseconds>(processing_end - load_data_end);
    auto total_duration = duration_cast<microseconds>(processing_end - load_data_start);

    std::ofstream log("results_via_std_map_timed.csv", std::ios_base::app | std::ios_base::out);
    // will save data in csv format > sample_size,load_time,processing_time,total_time
    log << argv[0] << "," << north_key_south_value.size() + 1 << "," << std::to_string(data_load_duration.count())
        << ","
        << std::to_string(processing_duration.count()) << "," << std::to_string(total_duration.count()) << std::endl;


#ifdef PRINT_OUT
    for (auto i: results_sequence) {
    std::cout << i << std::endl;
}
#endif


    return 0;
}