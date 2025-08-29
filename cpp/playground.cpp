//
// Created by Christoph Barth on 23.08.25.
//

#include <iostream>
#include "christorch/tensor/tensor.h"
#include "debug/nice_printing.h"

using namespace christorch;

int main() {

    std::vector<std::vector<float>> data = {{11,12,13},{21,22,23}};
    auto [flat, shape] = flatten_and_shape(data);
    Tensor a = Tensor(DType::Float32, shape);
    a.copyFrom(flat);

    Tensor b = Tensor({1.0,2.0,3.0});
    print_vector(b.shape());
    std::cout << to_string(b.dtype());

}