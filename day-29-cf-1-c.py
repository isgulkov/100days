
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __mul__(self, alpha):
        return Point(self.x * alpha, self.y * alpha)

    def __str__(self):
        return "(%.2f, %.2f)" % (self.x, self.y, )

class Line:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    @staticmethod
    def from_points(p1, p2):
        a = p1.y - p2.y
        b = p2.x - p1.x

        return Line._from_vector_and_point((a, b, ), p1)

    @staticmethod
    def _from_vector_and_point((vx, vy, ), p):
        return Line(vx, vy, - vx * p.x - vy * p.y)

    @staticmethod
    def _perp_vector(a, b):
        if b == 0:
            return 0.0, 1.0
        else:
            b_new = - 1.0 * a / b

            return 1.0, b_new

    def get_perp(self, p):
        a_new, b_new = self._perp_vector(self.a, self.b)

        return Line._from_vector_and_point((a_new, b_new, ), p)

    def __str__(self):
        return "[%.2fx + %.2fy + %.2f = 0]" % (self.a, self.b, self.c, )

def midpoint(p1, p2):
    return (p1 + p2) * 0.5

ps = []

for i in [1, 2, 3]:
    x, y = map(float, raw_input().split(' '))

    ps.append(Point(x, y))

l1 = Line.from_points(ps[0], ps[1])
l2 = Line.from_points(ps[1], ps[2])

m1 = midpoint(ps[0], ps[1])
m2 = midpoint(ps[1], ps[2])

print l1, l2

print l1.get_perp(m1), l2.get_perp(m2)
