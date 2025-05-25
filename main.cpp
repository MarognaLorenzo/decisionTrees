#include <vector>
#include <cmath>
#include <iostream>
#include "utils.h"
#include "DecisionTree.h"

int main() {
    matrix input_data = read_csv("data/data.csv");

    TrainLabelData data = get_train_label_data(input_data);

    DecisionTree dt = DecisionTree();
    dt.fit(data.trainData, data.labels);

    bool_vec instance = {true, false, false, true, false, false, true};
    std::cout << "result: " << (dt.predict(instance) ? "true" : "false" ) << std::endl;
    return 0;
}