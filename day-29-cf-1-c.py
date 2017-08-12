from math import sqrt, acos, pi, sin

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def dot(self, other):
        return self.x * other.x + self.y * other.y

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        # Multiply by number
        return Point(self.x * other, self.y * other)

    def __str__(self):
        return "(%.2f, %.2f)" % (self.x, self.y, )

    def __abs__(self):
        return sqrt(self.x ** 2 + self.y ** 2)

class Line:
    '''
    Build line from coefficients A, B, C of its equation "Ax + By + C = 0"
    '''
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    '''
    Build line from two points on it
    '''
    @staticmethod
    def from_points(p1, p2):
        a = p1.y - p2.y
        b = p2.x - p1.x

        return Line._from_vector_and_point((a, b, ), p1)

    '''
    Build line from direction vector and point on the line
    '''
    @staticmethod
    def _from_vector_and_point((vx, vy, ), p):
        return Line(vx, vy, - vx * p.x - vy * p.y)

    '''
    Returns vertor perpendicular to the given one (s.t. their dot product is zero)
    '''
    @staticmethod
    def _perp_vector(a, b):
        if b == 0:
            return 0.0, 1.0
        else:
            b_new = - 1.0 * a / b

            return 1.0, b_new

    '''
    Returns a line perpendicular to the current one that goes through point `p`
    '''
    def get_perp(self, p):
        a_new, b_new = self._perp_vector(self.a, self.b)

        return Line._from_vector_and_point((a_new, b_new, ), p)

    '''
    Returns the determinant the following matrix:
    [ `a00` `a01` ]
    [ `a10` `a11` ]
    '''
    @staticmethod
    def _det(a00, a01, a10, a11):
        return a00 * a11 - a01 * a10

    '''
    Returns the intersection point between the current line and `other`
    '''
    def intersect_with(self, other):
        delta = self._det(self.a, other.b, self.b, other.a)

        if delta == 0.0:
            raise Exception("ne peresekayutsia")

        x = self._det(self.c, self.b, other.c, other.b)
        y = self._det(self.a, self.c, other.a, other.c)

        return Point(x, y)

    def __str__(self):
        return "[%.2fx + %.2fy + %.2f = 0]" % (self.a, self.b, self.c, )

def midpoint(p1, p2):
    return (p1 + p2) * 0.5

# Returns radian measure of angle AOB, measured clockwise
def angle(a, o, b):
    oa = a - o
    ob = b - o

    phi = acos(1.0 * oa.dot(ob) / abs(oa) / abs(ob))

    if oa.y * ob.x - oa.x * ob.y < 0: # `ob` is counterclockwise to `oa`
        return 2.0 * pi - phi
    else:
        return phi

# Returns where it is possible for a `num-sides`-sided regular polygon to have some vertices at angles `alpha` and
# `beta` between each other
def regular_polygon_possible(num_vertices, alpha, beta):
    if alpha > beta:
        alpha, beta = beta, alpha

    return True

def regular_polygon_area(r_big, num_vertices):
    return num_vertices / 2.0 * r_big ** 2 * sin(2.0 * pi / num_vertices)


ps = []

for i in [1, 2, 3]:
    x, y = map(float, raw_input().split(' '))

    ps.append(Point(x, y))

l1 = Line.from_points(ps[0], ps[1])
l2 = Line.from_points(ps[1], ps[2])

m1 = midpoint(ps[0], ps[1])
m2 = midpoint(ps[1], ps[2])

center = l1.get_perp(m1).intersect_with(l2.get_perp(m2))

alpha = angle(ps[0], center, ps[1])
beta =  angle(ps[0], center, ps[2])

print alpha, beta

num_vertices = None

for i in xrange(3, 101):
    if regular_polygon_possible(i, alpha, beta):
        num_vertices = i
        break

print regular_polygon_area(abs(ps[0] - center), num_vertices)
