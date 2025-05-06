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
    int selected_index;
    bool_vec use;
    matrix tdata;




    float calculate_binary_entropy(std::vector<bool> & labels, std::vector<bool> & col){
        using namespace std;
        if (use.size() != labels.size()) throw invalid_argument("input sizes don't match");
        int total = count_if(use.begin(), use.end(), [](bool val){return val;});
        int total_positive = count_if(col.begin(), col.end(), [](bool val){return val;});
        int total_negative = total - total_positive;

        int pos_pos = 0, pos_neg = 0, neg_pos = 0, neg_neg = 0;
        for(int i = 0; i < use.size(); i++){
            if(!use[i]) continue;
            if(col[i]){
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
        float pos_entropy = fractionLog(pos_pos, total_positive) + fractionLog(pos_neg, total_positive);
        float neg_entropy = fractionLog(neg_pos, total_negative) + fractionLog(neg_neg, total_negative);
        if(verbose){
            cout << "pos pos " << pos_pos << endl;
            cout << "pos neg " << pos_neg << endl;
            cout << "neg pos " << neg_pos << endl;
            cout << "neg neg " << neg_neg << endl;
            cout << "pos entropy " << pos_entropy << endl;
            cout << "neg entropy " << neg_entropy << endl;
        }        

        float combined_entropy = frac(total_positive, total) * pos_entropy + frac(total_negative, total) * neg_entropy;
        return combined_entropy;
    }

    std::vector<bool> get_col(matrix m, int column){
        std::vector<bool> row;
        for(int i = 0; i< m.size(); i++){
            row.push_back(use[i] && m[i][column]);
        }
        return row;
    }

    float entropy_split(matrix & data, bool_vec & labels, int column){
        std::vector<bool> col = get_col(data, column);
        float result = calculate_binary_entropy(labels, col);
        return result;
    }

public:
    DecisionTree(bool v){
        verbose = v;
        return;
    }
    DecisionTree(bool_vec use){
        this->use = use;
    }

    void fit(std::vector<std::vector<bool> > & data, std::vector<bool> & labels){
        if(data.size() == 0) return;
        for(auto el: data) {
            if (el.size() != data.at(0).size()) throw std::invalid_argument("Matrix shape is inconsistent");
        }
        this->data = data;
        int split_index = decide_split(data, labels);


    } 

    int predict(std::vector<bool> & instance) {
        return 0;
    }
    int get_positive(std::vector<bool> & labels){
        return 0;
    }

    int decide_split(matrix & data, bool_vec & labels){
        float smaller_entropy = -1;
        int best_index;
        int s = data.size();
        for(int i = 0; i < data[0].size(); i++){
            float entropy = entropy_split(data, labels, i);
            std::cout << " entopy " << entropy << " at index " << i << std::endl;
            if(entropy > smaller_entropy){
                smaller_entropy = entropy;
                best_index = i;
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
    DecisionTree dt(false);
    matrix data = read_csv("data.csv");
    matrix r = transpose(data);
    auto parsed_data = get_train_test_data(data);
    matrix train_data = parsed_data.first;
    bool_vec labels = parsed_data.second; 
    int best_split = dt.decide_split(train_data, labels);
    std::cout << "best split: " << best_split << std::endl;
    return 0;
}