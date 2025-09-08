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

        size_t posToIdx(const std::vector<size_t>& pos) const {
            if (pos.size() != shape_.size())
                throw std::runtime_error("Tensor::posToIdx: got " + std::to_string(pos.size()) +
                                         " indices but tensor has " + std::to_string(shape_.size()) + " dims");
            if (pos.empty())
                throw std::runtime_error("Tensor::posToIdx: empty position");

            // Bounds check
            for (size_t i = 0; i < pos.size(); ++i) {
                if (pos[i] >= shape_[i]) {
                    throw std::runtime_error("Tensor::posToIdx: index " + std::to_string(pos[i]) +
                                             " out of bounds for dim " + std::to_string(i) +
                                             " with size " + std::to_string(shape_[i]));
                }
            }

            // Row-major: stride_i = product(shape_[i+1..end])
            size_t idx = 0;
            size_t stride = 1;
            for (size_t i = pos.size(); i-- > 0; ) {      // i = n-1, n-2, ..., 0
                idx += pos[i] * stride;
                if (i > 0) stride *= shape_[i];          // prepare stride for the next (left) dim
            }

            if (idx >= size_)
                throw std::runtime_error("Tensor::posToIdx: linear index " + std::to_string(idx) +
                                         " out of range for tensor size " + std::to_string(size_));
            return idx;
        }


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

        num& get(std::vector<size_t> pos) {
            return data_[posToIdx(pos)];
        }

        num& get(std::initializer_list<size_t> pos) {
            return data_[posToIdx(std::vector<size_t>(pos))];
        }



        // Element access (bounds-checked)
        num& at(size_t idx);
        const num& at(size_t idx) const;

        // Copy in/out
        void copyFrom(const std::vector<num>& src);
        std::vector<num> to_vector() const;
    };

} // namespace christorch
