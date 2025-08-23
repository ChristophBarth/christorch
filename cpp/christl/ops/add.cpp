#include "christl/ops/add.h"
namespace christl {
Tensor add(const Tensor& a, const Tensor& b) {
    if (a.size() != b.size()) throw std::runtime_error("size mismatch");
    Tensor out(std::vector<double>(a.size()));
    for (size_t i = 0; i < a.size(); ++i) out.set(i, a.get(i)+b.get(i));
    return out;
}
}
