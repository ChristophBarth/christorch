#include "add.h"
#include <stdexcept>
#include "debug/nice_printing.h"
#include "core/type.h"


namespace christorch {
    
    Tensor add(const Tensor& a, const Tensor& b) {
        if(a.shape() != b.shape()){
            throw std::runtime_error(
                    "shape mismatch in add(): Tensor a" + vec_to_str(a.shape()) + "; Tensor b" + vec_to_str(b.shape())
            );
        }

        Tensor out(a.shape());
        const num* pa = a.data();
        const num* pb = b.data();
        num* pc = out.data();
        for (size_t i = 0; i < a.size(); ++i) {
            pc[i] = pa[i] + pb[i];
        }
        return out;
        
    }
} // namespace christorch
