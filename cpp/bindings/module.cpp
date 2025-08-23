#include <pybind11/pybind11.h>
namespace py = pybind11;
void init_tensor_bindings(py::module_&);

PYBIND11_MODULE(_C, m) {
  m.doc() = "christorch C++ backend";
  init_tensor_bindings(m);
}
