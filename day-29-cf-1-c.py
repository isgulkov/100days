
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
    def __init__(self, p1, p2):
        self.a = p2.y - p1.y
        self.b = p2.x - p1.x
        self.c = p1.x * p2.y - p2.x * p1.y

    def __str__(self):
        return "[%.2fx + %.2fy + %.2f = 0]" % (self.a, self.b, self.c, )

def midpoint(p1, p2):
    return (p1 + p2) * 0.5

ps = []

for i in [1, 2, 3]:
    x, y = map(float, raw_input().split(' '))

    ps.append(Point(x, y))

print Line(ps[0], ps[1]), Line(ps[0], ps[2]), Line(ps[1], ps[2])

print midpoint(ps[0], ps[1]), midpoint(ps[1], ps[2])
