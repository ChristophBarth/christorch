//
// Created by Christoph Barth on 23.08.25.
//

#include <iostream>
#include "christorch/tensor/tensor.h"
#include "debug/nice_printing.h"
#include "christorch/ops/add.h"
#include "christorch/ops/matmul.h"

using namespace christorch;

int main() {

    std::vector<std::vector<float>> dataA = {{1,1},{0,1}};
    auto [flatA, shapeA] = flatten_and_shape(dataA);
    Tensor a = Tensor(DType::Float32, shapeA);
    a.copyFrom(flatA);

    std::vector<std::vector<float>> data = {{1,0},{2,1}};
    auto [flatB, shapeB] = flatten_and_shape(data);
    Tensor b = Tensor(DType::Float32, shapeB);
    b.copyFrom(flatB);

    Tensor c = matmul(a,b);

    print_vector(c.to_vector<float>());

}