#include "utils.h"
#include <fstream>
#include <sstream>

matrix read_csv(const std::string& filename) {
    matrix data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    std::string line;
    
    while (std::getline(file, line)) {
        bool_vec row;
        std::stringstream ss(line);
        std::string value;
        
        while (std::getline(ss, value, ',')) {
            row.push_back(value == "1" || value == "true" || value == "True");
        }
        
        if (!row.empty()) {
            data.push_back(row);
        }
    }
    
    return data;
}