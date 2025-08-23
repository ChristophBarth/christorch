from christorch import Tensor

def test_add_simple():
    a = Tensor([1,2,3])
    b = Tensor([10,20,30])
    c = a + b
    assert c.tolist() == [11.0, 22.0, 33.0]
