#include <vector>
#include <cmath>
#include <iostream>
#include "utils.h"
#include "DecisionTree.h"

int main() {
    matrix data = read_csv("data/data.csv");

    auto parsed_data = get_train_test_data(data);
    matrix train_data = parsed_data.first;
    bool_vec labels = parsed_data.second; 

    DecisionTree dt = DecisionTree();
    dt.fit(train_data, labels);

    bool_vec instance = {true, false, false, true, false, false, true};
    std::cout << "result: " << (dt.predict(instance) ? "true" : "false" ) << std::endl;
    return 0;
}