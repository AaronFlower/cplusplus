import math


class Var():

    def __init__(self, v):
        self.value = v
        self.children = []
        self.grad = None

    def Grad(self):
        if len(self.children) == 0:
            return 1.0

        if self.grad is None:
            self.grad = sum([w * var.Grad() for w, var in self.children])
        return self.grad

    def __add__(self, other):
        res = Var(self.value + other.value)
        self.children.append([1.0, res])
        other.children.append([1.0, res])
        return res

    def __mul__(self, other):
        res = Var(self.value * other.value)
        self.children.append([other.value, res])
        other.children.append([self.value, res])
        return res


def sin(var):
    res = Var(math.sin(var.value))
    var.children.append([math.cos(var.value), res])
    return res


def main():
    x = Var(2)
    y = Var(3)
    z = x * y + sin(x)
    dz_x = x.Grad()
    dz_y = y.Grad()

    print('z = ', z.value, z.Grad())
    print('dz_x = ', dz_x)
    print('dz_y = ', dz_y)


if __name__ == "__main__":
    main()
