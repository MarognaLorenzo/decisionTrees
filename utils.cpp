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


float frac(int count, int total){
    return (float) count / total;
}

float fractionLog(int count, int total){
    if (count == 0) return 0;
    float fraction = frac(count, total);
    return fraction * std::log2(fraction);
}


matrix transpose(matrix & data){
    if (data.size() == 0) return {};
    matrix result (data[0].size());
    for(int r = 0; r < data[0].size(); r++){
        bool_vec v (data.size());
        result[r] = v;
    }
    for(int r = 0; r < data.size(); r++){
        for(int c = 0; c < data[0].size(); c++){
            result[c][r] = data[r][c];
        }
    }
    return result;
}