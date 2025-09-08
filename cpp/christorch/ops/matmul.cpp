#include "matmul.h"
#include <stdexcept>
#include "debug/nice_printing.h"
#include "core/type.h"

namespace christorch {

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

        std::vector<size_t> outShape = {a.shape()[0], b.shape()[1]};
        Tensor out(outShape);
        const num* pa = a.data();
        const num* pb = b.data();
        num* pc = out.data();

        for(size_t r=0;r<a.shape()[0];r++){
            for(size_t c=0;c<b.shape()[1];c++){
                num tmp = 0;
                for(size_t i=0;i<a.shape()[1];i++){
                    tmp = tmp + pa[r * a.shape()[0] + i] * pb[i * b.shape()[0] + c];
                }
                pc[r * a.shape()[0] + c] = tmp;
            }
        }

        return out;


    }
} // namespace christorch
