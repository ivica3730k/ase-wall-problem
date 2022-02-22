#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <unordered_map>

using STORAGE_STRUCTURE = std::unordered_map<std::string, std::string>;

int main(int argc, char *argv[]) {
    STORAGE_STRUCTURE north_key_south_value;
    STORAGE_STRUCTURE south_key_north_value;

    // Load data into memory
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
    for (auto i: results_sequence) {
        std::cout << i << std::endl;
    }
    return 0;
}