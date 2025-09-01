//
// Created by Christoph Barth on 23.08.25.
//

#include <iostream>
#include "christorch/tensor/tensor.h"
#include "debug/nice_printing.h"
#include "christorch/ops/add.h"

using namespace christorch;

int main() {

    std::vector<std::vector<float>> data = {{11,12,13},{21,22,23}};
    auto [flat, shape] = flatten_and_shape(data);
    Tensor a = Tensor(DType::Float32, shape);
    a.copyFrom(flat);

    Tensor b = Tensor({{11,12,13,21,22,23}});

    Tensor c  = add(b,b);
    print_vector(c.to_vector<int>());
}