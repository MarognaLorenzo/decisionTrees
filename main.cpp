#include <vector>
#include <cmath>
#include <iostream>
#include "utils.h"

class DecisionTree {
public:
    bool verbose;
    DecisionTree* right;
    DecisionTree* left;
    matrix data;
    int splitting_column;
    std::vector<int> rows_to_use;
    std::vector<int> cols_to_use;
    matrix tdata;
    bool_vec labels;
    bool root;

    float calculate_binary_entropy(int column){
        using namespace std;
        int total = rows_to_use.size();

        int pos_pos = 0, pos_neg = 0, neg_pos = 0, neg_neg = 0;
        for(int i = 0; i < rows_to_use.size(); i++){
            if(tdata[column][i]){
                if(labels[i]){
                    pos_pos ++;
                } else {
                    pos_neg ++;
                }
            } else {
                if(labels[i]){
                    neg_pos ++;
                } else {
                    neg_neg ++;
                }
            }
        }
        float pos_entropy = fractionLog(pos_pos, pos_pos + pos_neg) + fractionLog(pos_neg, pos_pos + pos_neg);
        float neg_entropy = fractionLog(neg_pos, neg_pos + neg_neg) + fractionLog(neg_neg, neg_pos + neg_neg);
        if(verbose){
            cout << "pos pos " << pos_pos << endl;
            cout << "pos neg " << pos_neg << endl;
            cout << "neg pos " << neg_pos << endl;
            cout << "neg neg " << neg_neg << endl;
            cout << "pos entropy " << pos_entropy << endl;
            cout << "neg entropy " << neg_entropy << endl;
        }        

        float combined_entropy = frac(pos_pos + pos_neg, total) * pos_entropy + frac(neg_pos + neg_neg, total) * neg_entropy;
        return combined_entropy;
    }

public:
    DecisionTree(){
        verbose = false;
        root = true;
    }
    DecisionTree(bool v){
        verbose = v;
        root = true;
        return;
    }
    DecisionTree(DecisionTree & parentTree, std::vector<int> _rows_to_use, std::vector<int> _cols_to_use){
        data = parentTree.data;
        tdata = parentTree.tdata;
        labels = parentTree.labels;
        rows_to_use = _rows_to_use;
        cols_to_use = _cols_to_use;
        root = false;
    }
    
    void fit(matrix & _data, bool_vec & _labels){
        // if(rows_to_use.size() == 0 || cols_to_use.size() == 0) return;
        if(root){
            for(auto el: data) {
                if (el.size() != data.at(0).size()) throw std::invalid_argument("Matrix shape is inconsistent");
            }
            data = _data;
            labels = _labels;
            tdata = transpose(data);
            
            // Set all rows to be used
            rows_to_use = std::vector<int> (data.size());
            for(int i = 0; i < data.size(); i++) rows_to_use[i] = i;
            
            // Set all columns to be used
            cols_to_use = std::vector<int> (data[0].size());
            for(int i = 0; i < data[0].size(); i++) cols_to_use[i] = i;
        }

        int best_col = decide_split();

        splitting_column = best_col;

        std::vector<int> cols_left;
        std::copy_if(cols_to_use.begin(), cols_to_use.end(), std::back_inserter(cols_left), [&best_col](int i){return i != best_col;});

        std::vector<int> cols_right(cols_left.begin(), cols_left.end());


        left = new DecisionTree(this);
        right = new DecisionTree(this);

    } 

    int predict(std::vector<bool> & instance) {
        return 0;
    }
    int get_positive(std::vector<bool> & labels){
        return 0;
    }

    int decide_split(){
        float smaller_entropy = -1;
        int best_index;
        for(int feature: cols_to_use){
            float entropy = calculate_binary_entropy(feature);
            std::cout << " entopy " << entropy << " at index " << feature << std::endl;
            if(entropy > smaller_entropy){
                smaller_entropy = entropy;
                best_index = feature;
            }
        }
        return best_index;
    }
};

std::pair<matrix, bool_vec> get_train_test_data(matrix data){
    matrix train_data;
    bool_vec labels;
    for(auto row: data){
        labels.push_back(row.back());
        train_data.push_back(std::vector<bool>());
        for(auto el: row) train_data.back().push_back(el);
        train_data.back().pop_back();
    }
    return {train_data, labels};
}

int main() {
    matrix data = read_csv("data.csv");
    auto parsed_data = get_train_test_data(data);
    matrix train_data = parsed_data.first;
    bool_vec labels = parsed_data.second; 
    DecisionTree dt = DecisionTree();
    dt.fit(train_data, labels);
    return 0;
}