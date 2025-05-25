#include "DecisionTree.h"
#include <algorithm>
#include <iostream>

float DecisionTree::calculate_binary_entropy(int column){
    using namespace std;
    int total = rows_to_use.size();

    int pos_pos = 0, pos_neg = 0, neg_pos = 0, neg_neg = 0;
    for(auto row: rows_to_use){
        if(data[row][column]){
            if(labels[row]){
                pos_pos ++;
            } else {
                pos_neg ++;
            }
        } else {
            if(labels[row]){
                neg_pos ++;
            } else {
                neg_neg ++;
            }
        }
    }
    float pos_entropy = fractionLog(pos_pos, pos_pos + pos_neg) + fractionLog(pos_neg, pos_pos + pos_neg);
    float neg_entropy = fractionLog(neg_pos, neg_pos + neg_neg) + fractionLog(neg_neg, neg_pos + neg_neg);   

    float combined_entropy = frac(pos_pos + pos_neg, total) * pos_entropy + frac(neg_pos + neg_neg, total) * neg_entropy;
    return combined_entropy;
}

float DecisionTree::calculate_class_entropy(){
    int total = rows_to_use.size();
    int count = std::count_if(rows_to_use.begin(), rows_to_use.end(), [this](int row){return labels[row];});
    float class_entropy = fractionLog(count, total) + fractionLog(total - count, total);
    return class_entropy;
}

DecisionTree::DecisionTree(){
    root = true;
}
DecisionTree::DecisionTree(bool v){
    root = true;
    return;
}
DecisionTree::DecisionTree(DecisionTree & parentTree, std::vector<int> _rows_to_use, std::vector<int> _cols_to_use){
    data = parentTree.data;
    labels = parentTree.labels;
    rows_to_use = _rows_to_use;
    cols_to_use = _cols_to_use;
    root = false;
}

void DecisionTree::_fit(){
    std::cout << "cols:" << cols_to_use.size() << "\nrows: " << rows_to_use.size() << "\n";
    if(rows_to_use.size() == 0 || cols_to_use.size() == 0 ){
        return;
    } 
    if(calculate_class_entropy() == 0){
        std::cout << "\tstopping" << std::endl;
        prediction = labels[rows_to_use[0]];
        splitting_column = -1;
        return;
    }
    splitting_column = decide_split();
    std::cout << "I am splitting on " << splitting_column << std::endl;

    std::vector<int> cols_left;
    std::copy_if(cols_to_use.begin(), cols_to_use.end(), std::back_inserter(cols_left), [this](int i){return i != splitting_column;});

    std::vector<int> cols_right(cols_left.begin(), cols_left.end());

    // TODO FIX THIS
    std::vector<int> rows_left;
    std::copy_if(rows_to_use.begin(), rows_to_use.end(), std::back_inserter(rows_left), [this](int row){return data[row][splitting_column];});

    std::vector<int> rows_right;
    std::copy_if(rows_to_use.begin(), rows_to_use.end(), std::back_inserter(rows_right), [this](int row){return !data[row][splitting_column];});

    std::cout << "\ngoing left (true)" << std::endl;
    left = new DecisionTree(*this, rows_left, cols_left);
    left->_fit();

    std::cout << "\ngoing right (false)" << std::endl;
    right = new DecisionTree(*this, rows_right, cols_right);
    right->_fit();
}

void DecisionTree::fit(matrix & _data, bool_vec & _labels){
    for(auto el: data) {
        if (el.size() != data.at(0).size()) throw std::invalid_argument("Matrix shape is inconsistent");
    }
    data = _data;
    labels = _labels;
    
    // Set all rows to be used
    rows_to_use = std::vector<int> (data.size());
    for(int i = 0; i < data.size(); i++) rows_to_use[i] = i;
    
    // Set all columns to be used
    cols_to_use = std::vector<int> (data[0].size());
    for(int i = 0; i < data[0].size(); i++) cols_to_use[i] = i;

    _fit();
} 

int DecisionTree::predict(std::vector<bool> & instance) {
    std::cout << "Deciding on colum: " << splitting_column << " " << (instance[splitting_column] ? "true" : "false" ) << std::endl;
    if (splitting_column < 0) return prediction;
    if(instance[splitting_column]) return left->predict(instance);
    else return right->predict(instance);
}

int DecisionTree::decide_split(){
    float smaller_entropy = -100;
    int best_index;
    // std::cout << "--------------- \n cols: ";

    for(int feature: cols_to_use){
        float entropy = calculate_binary_entropy(feature);
        // std::cout << "\t entopy " << entropy << " at index " << feature << std::endl;
        if(entropy > smaller_entropy){
            smaller_entropy = entropy;
            best_index = feature;
        }
    }
    std::cout << "Selected feature " << best_index << " with entropy " << smaller_entropy << std::endl;
    return best_index;
}