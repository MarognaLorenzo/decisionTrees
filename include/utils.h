#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

typedef std::vector<bool> bool_vec;
typedef std::vector<bool_vec> matrix;

matrix read_csv(const std::string& filename);

float frac(int count, int total);

float fractionLog(int count, int total);

matrix transpose(matrix & data);

std::pair<matrix, bool_vec> get_train_test_data(matrix data);
#endif // UTILS_H