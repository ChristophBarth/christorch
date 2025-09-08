#include "tensor.h"
#include <stdexcept>
#include "core/utils.h"

namespace christorch {

    Tensor::Tensor(std::vector<size_t> shape)
            : shape_(std::move(shape))  // move once
    {
        size_ = numEl(shape_);     // use the member (not moved-from)
        data_.assign(size_, 0.0f); // or data_.resize(size_);
    }


    Tensor::Tensor(std::initializer_list<num> data) {
        // If your flatten_and_shape overload expects nested lists, keep that version instead.
        auto [flat, shape] = flatten_and_shape(data);
        shape_ = std::move(shape);
        size_  = flat.size();
        data_  = std::move(flat);
    }

    num& Tensor::at(size_t idx) {
        if (idx >= size_) throw std::out_of_range("Tensor::at index out of range");
        return data_[idx];
    }

    const num& Tensor::at(size_t idx) const {
        if (idx >= size_) throw std::out_of_range("Tensor::at index out of range");
        return data_[idx];
    }

    void Tensor::copyFrom(const std::vector<num>& src) {
        if (src.size() != size_) {
            throw std::runtime_error("size mismatch in Tensor::copyFrom - expected " + std::to_string(size_) + " but got " + std::to_string(src.size()));
        }
        data_ = src;
    }

    std::vector<num> Tensor::to_vector() const {
        return data_;
    }

} // namespace christorch
