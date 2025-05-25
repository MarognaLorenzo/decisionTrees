#ifndef DECISIONTREEH
#define DECISIONTREEH
#include "utils.h"
class DecisionTree {
public:
    DecisionTree* right;
    DecisionTree* left;
    matrix data;
    int splitting_column;
    std::vector<int> rows_to_use;
    std::vector<int> cols_to_use;
    bool_vec labels;
    bool root;
    bool prediction;

    float calculate_binary_entropy(int column);
    float calculate_class_entropy();

    DecisionTree();
    DecisionTree(bool v);
    DecisionTree(DecisionTree & parentTree, std::vector<int> _rows_to_use, std::vector<int> _cols_to_use);

    void _fit();
    void fit(matrix & _data, bool_vec & _labels);

    int predict(std::vector<bool> & instance);

    int decide_split();
};

#endif