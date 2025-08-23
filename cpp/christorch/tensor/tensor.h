#pragma once
#include <vector>
#include <stdexcept>
#include <numeric>

namespace christorch {
class Tensor {
public:
    Tensor() = default;
    explicit Tensor(std::vector<double> data) : data_(std::move(data)) {}
    size_t size() const { return data_.size(); }
    double get(size_t i) const { return data_.at(i); }
    void set(size_t i, double v) { data_.at(i) = v; }
    const std::vector<double>& data() const { return data_; }
    std::vector<double>& data() { return data_; }
private:
    std::vector<double> data_;
};
} // namespace christorch
