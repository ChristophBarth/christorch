//
// Created by Christoph Barth on 23.08.25.
//

#include <iostream>
#include <numeric>
#include "christorch/tensor/tensor.h"
#include "debug/nice_printing.h"
#include "christorch/ops/add.h"
#include "christorch/ops/matmul.h"
#include "core/utils.h"

using namespace christorch;

int main() {

    std::vector<std::vector<float>> dataA = {{1,1},{0,1}};
    auto [flatA, shapeA] = flatten_and_shape(dataA);

    print_vector(shapeA, "Shape A");
    std::cout << std::to_string(numEl(shapeA)) << " Size A \n";

    Tensor a = Tensor(shapeA);
    std::cout << std::to_string(a.size()) << " returned from a.size() \n";
    a.copyFrom(flatA);


    std::vector<std::vector<float>> data = {{1,0},{2,1}};
    auto [flatB, shapeB] = flatten_and_shape(data);
    Tensor b = Tensor(shapeB);
    b.copyFrom(flatB);

    Tensor c = matmul(a,b);

    print_vector(c.to_vector());

}