#include "add.h"
#include <stdexcept>
#include "debug/nice_printing.h"


namespace christorch {

    template<typename T>
    static Tensor add_impl(const Tensor& a, const Tensor& b) {
        Tensor out(a.dtype(), a.shape());
        const T* pa = a.data_as<T>();
        const T* pb = b.data_as<T>();
        T* pc = out.data_as<T>();
        for (size_t i = 0; i < a.size(); ++i) {
            pc[i] = pa[i] + pb[i];
        }
        return out;
    }

    Tensor add(const Tensor& a, const Tensor& b) {
        if(a.shape() != b.shape()){
            throw std::runtime_error(
                    "shape mismatch in add(): Tensor a" + vec_to_str(a.shape()) + "; Tensor b" + vec_to_str(b.shape())
            );
        }
        if(a.dtype() != b.dtype()){
            throw std::runtime_error("dtype mismatch in add(): Tensor a is" + to_string(a.dtype()) + "; Tensor b is" +
                                     to_string(b.dtype()));
        }

        switch (a.dtype()) {
            case DType::Float32: return add_impl<float>(a, b);
            case DType::Float64: return add_impl<double>(a, b);
            case DType::Int32:   return add_impl<int32_t>(a, b);
            case DType::Int64:   return add_impl<int64_t>(a, b);
            default: throw std::runtime_error("unsupported dtype");
        }
    }
} // namespace christorch
