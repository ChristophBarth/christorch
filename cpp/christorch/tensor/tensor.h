#pragma once
#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <utility>   // for std::move, std::pair
#include "core/dtype.h"     // itemsize(DType), CTypeToDType<T>::value, to_string(DType)
#include "core/utils.h"   // flatten_and_shape(initializer_list<T>)->pair<vector<T>, vector<size_t>>

namespace christorch {

    class Tensor {
    private:
        // Raw storage (dtype-sized bytes)
        std::shared_ptr<void> data_{nullptr};
        std::vector<size_t> shape_;
        DType dtype_{DType::UNDEFINED};  // Adjust if you have another default
        size_t size_{0};

    public:
        // Constructors
        Tensor(DType dtype, std::vector<size_t> shape):
            dtype_(dtype), shape_(shape){
            size_ = numel(shape);
            data_ = std::shared_ptr<void>(
                    operator new(itemsize(dtype) * size_),
                    [](void* p) { operator delete(p); }
                    );
        }

        template<typename T>
        Tensor(std::initializer_list<T> data);

        // Observers
        inline const size_t size() const { return size_; }
        inline const std::vector<size_t>& shape() const { return shape_; }
        inline const DType dtype() const { return dtype_; }

        // Typed data access
        template<typename T>
        T* data_as();

        template<typename T>
        const T* data_as() const;

        // Copy in/out
        template<typename T>
        void copyFrom(const std::vector<T>& src);

        template<typename T>
        std::vector<T> to_vector() const;

        template<typename T>
        const T* get(size_t idx) const;
    };


// ---------- Template impls must live in the header ----------

    template<typename T>
    Tensor::Tensor(std::initializer_list<T> data){
        auto [flat, shape] = flatten_and_shape(data);
        shape_ = shape;
        size_ = numel(shape_);
        dtype_ = CTypeToDType<T>::value;
        data_ = std::shared_ptr<void>(
                operator new(itemsize(dtype_) * size_),
                [](void* p) { operator delete(p); }
        );
        copyFrom(flat);
    }


    template<typename T>
    inline T* Tensor::data_as() {
        const DType expected = CTypeToDType<T>::value;
        if (expected != dtype_) {
            throw std::runtime_error(
                    "dtype mismatch in data_as(): Tensor holds " +
                    to_string(dtype_) + " but requested " + to_string(expected)
            );
        }
        return reinterpret_cast<T*>(data_.get());
    }

    template<typename T>
    inline const T* Tensor::data_as() const {
        const DType expected = CTypeToDType<T>::value;
        if (expected != dtype_) {
            throw std::runtime_error(
                    "dtype mismatch in data_as() const: Tensor holds " +
                    to_string(dtype_) + " but requested " + to_string(expected)
            );
        }
        return reinterpret_cast<const T*>(data_.get());
    }

    template<typename T>
    inline void Tensor::copyFrom(const std::vector<T>& src){
        if (src.size() != size_) {
            throw std::runtime_error("size mismatch in copyFrom(): src.size()=" +
                                     std::to_string(src.size()) + " vs tensor size_=" +
                                     std::to_string(size_));
        }
        T* dest = data_as<T>();
        std::copy(src.begin(), src.end(), dest);
    }

    template<typename T>
    inline std::vector<T> Tensor::to_vector() const {
        const T* src = data_as<T>();
        return std::vector<T>(src, src + size_);
    }

    template<typename T>
    inline const T* Tensor::get(size_t idx) const {
       if(idx >= size_){
           throw std::runtime_error(
                   "In Tensor.get(): Index " + std::to_string(idx) + " out of bounds for tensor size " + std::to_string(size_)
                   );
       }
       return data_as<T>() + idx;
    }

} // namespace christorch