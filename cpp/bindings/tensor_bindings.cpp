#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "christorch/tensor/tensor.h"
#include "christorch/ops/add.h"

namespace py = pybind11;

void init_tensor_bindings(py::module_& m) {
    py::class_<christorch::Tensor>(m, "TensorNative")
        //.def(py::init<std::vector<double>>(), py::arg("data"))
        .def("size", &christorch::Tensor::size)
        .def("data", [](christorch::Tensor& t){ return t.data(); });

    m.def("add_native", [](const christorch::Tensor& a, const christorch::Tensor& b){
        return christorch::add(a,b);
    });
}
