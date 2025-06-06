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


typedef struct TrainLabelData{
    matrix trainData;
    bool_vec labels;
    
    ~TrainLabelData();
    TrainLabelData();
    TrainLabelData(matrix _train, bool_vec _labels);
    matrix get_train_data();
} TrainLabelData;

TrainLabelData get_train_label_data(matrix data);
#endif // UTILS_H
