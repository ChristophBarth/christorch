from . import _C
class Tensor:
    def __init__(self, data):
        if isinstance(data, _C.TensorNative):
            self._native = data
        else:
            self._native = _C.TensorNative(list(map(float,data)))
    def __add__(self, other):
        return Tensor(_C.add_native(self._native, other._native))
    def tolist(self):
        return list(self._native.data())
    def __repr__(self):
        return f"Tensor({self.tolist()})"
