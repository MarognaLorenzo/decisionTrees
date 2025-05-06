#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

typedef std::vector<bool> bool_vec;
typedef std::vector<bool_vec> matrix;

matrix read_csv(const std::string& filename);

#endif // UTILS_H