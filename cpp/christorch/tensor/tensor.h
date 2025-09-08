#pragma once
#include <vector>
#include <initializer_list>
#include "core/type.h"

namespace christorch {

    class Tensor {
    private:
        std::vector<size_t> shape_;
        size_t size_{0};
        std::vector<num> data_;

    public:
        // Constructors
        explicit Tensor(std::vector<size_t> shape);
        Tensor(std::initializer_list<num> data); // expects your flatten_and_shape<num>()

        // Observers
        size_t size() const { return size_; }
        const std::vector<size_t>& shape() const { return shape_; }

        // Data access
        num* data() { return data_.data(); }
        const num* data() const { return data_.data(); }

        num& get(size_t idx) {
            if (idx >= size_) throw std::out_of_range("Tensor::get");
            return data_[idx];
        }

        const num& get(size_t idx) const {
            if (idx >= size_) throw std::out_of_range("Tensor::get");
            return data_[idx];
        }


        // Element access (bounds-checked)
        num& at(size_t idx);
        const num& at(size_t idx) const;

        // Copy in/out
        void copyFrom(const std::vector<num>& src);
        std::vector<num> to_vector() const;
    };

} // namespace christorch
