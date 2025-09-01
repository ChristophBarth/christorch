#include "matmul.h"
#include <stdexcept>
#include "debug/nice_printing.h"

namespace christorch {

    template<typename T>
    static Tensor matmul_impl(const Tensor& a, const Tensor& b) {
        std::vector<size_t> outShape = {a.shape()[0], b.shape()[1]};
        Tensor out(a.dtype(), outShape);
        const T* pa = a.data_as<T>();
        const T* pb = b.data_as<T>();
        T* pc = out.data_as<T>();

        for(size_t r=0;r<a.shape()[0];r++){
            for(size_t c=0;c<b.shape()[1];c++){
                T tmp = 0;
                for(size_t i=0;i<a.shape()[1];i++){
                    tmp = tmp + pa[r * a.shape()[0] + i] * pb[i * b.shape()[0] + c];
                }
                pc[r * a.shape()[0] + c] = tmp;
            }
        }

        return out;
    }

    Tensor matmul(const Tensor& a, const Tensor& b) {
        if(a.shape().size() != 2){
            throw std::runtime_error(
                    "Non Matrix argument in matmul(): Tensor a has dimension " + std::to_string(a.size())
            );
        }
        if(b.shape().size() != 2){
            throw std::runtime_error(
                    "Non Matrix argument in matmul(): Tensor b has dimension " + std::to_string(b.size())
            );
        }
        if(a.shape()[1] != b.shape()[0]){
            throw std::runtime_error(
                    "shape mismatch in matmul(): Tensor a" + vec_to_str(a.shape()) + "; Tensor b" + vec_to_str(b.shape())
            );
        }
        if(a.dtype() != b.dtype()){
            throw std::runtime_error("dtype mismatch in matmul(): Tensor a is" + to_string(a.dtype()) + "; Tensor b is" +
                                     to_string(b.dtype()));
        }

        switch (a.dtype()) {
            case DType::Float32: return matmul_impl<float>(a, b);
            case DType::Float64: return matmul_impl<double>(a, b);
            case DType::Int32:   return matmul_impl<int32_t>(a, b);
            case DType::Int64:   return matmul_impl<int64_t>(a, b);
            default: throw std::runtime_error("unsupported dtype");
        }
    }
} // namespace christorch
