CALC_EPS = 1e-8


class Point:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def get_middle(self, other):
        new = Point(self.x, self.y, self.z)
        new.x = (new.x + other.x) / 2
        new.y = (new.y + other.y) / 2
        new.z = (new.z + other.z) / 2

        return new

    def copy(self):
        return Point(self.x, self.y, self.z)

def get_distance(point1: Point, point2: Point):
    return ((point2.x - point1.x) ** 2 
            + (point2.y - point1.y) ** 2 
            + (point2.z - point1.z) ** 2) ** 0.5


class Vector:
    def __init__(self):
        self.dx = 0
        self.dy = 0
        self.dz = 0

    def init(self, dx, dy, dz):
        self.dx = dx
        self.dy = dy
        self.dz = dz

        return self

    def init_points(self, point1, point2):
        self.dx = point2.x - point1.x
        self.dy = point2.y - point1.y
        self.dz = point2.z - point1.z

        return self
    
    def __add__(self, other):
        new = Vector();
        new.dx = self.dx + other.dx
        new.dy = self.dy + other.dy
        new.dz = self.dz + other.dz

        return new
    
    def __sub__(self, other):
        new = Vector();
        new.dx = self.dx - other.dx
        new.dy = self.dy - other.dy
        new.dz = self.dz - other.dz

        return new

    def __mul__(self, other):
        new = Vector();
        new.dx = self.dy * other.dz - self.dz * other.dy
        new.dy = -(self.dx * other.dz - self.dz * other.dx)
        new.dz = self.dx * other.dy - self.dy * other.dx

        return new

    def scalar_mul(self, other):
        return self.dx * other.dx + self.dy * other.dy + self.dz * other.dz

    def length(self):
        return (self.dx ** 2 + self.dy ** 2 + self.dz ** 2) ** 0.5

    def normalize(self):
        length = self.length()

        return self.adjust(1 / self.length()) \
               if CALC_EPS < abs(length)      \
               else self

    def get_normalXY(self):
        new = Vector();
        new.dx, new.dy = -self.dy, self.dx

        return new;

    def adjust(self, value):
        self.dx *= value
        self.dy *= value
        self.dz *= value

        return self

    def is_collinear(self, other):
        if (True in [CALC_EPS > abs(i.length()) for i in [self, other]]):
            return False

        # result = (self.copy().normalize() + other.copy().normalize()).length()
        #  
        # if CALC_EPS > abs(result) or CALC_EPS > abs(result - 2):
        #     return True
        #  
        # return False

        out = True
        k = None

        for i, j in ((self.dx, other.dx), (self.dy, other.dy), (self.dz, other.dz)):
            if not out:
                continue

            if (CALC_EPS > abs(i) or CALC_EPS > abs(j)):
                if CALC_EPS < abs(i - j):
                    out = False
            elif k is None:
                k = i / j
            elif CALC_EPS < abs(k - i / j):
                out = False

        return out

    def get_start(self, end: Point):
        start = Point(end.x, end.y, end.z)
        start.x -= self.dx
        start.y -= self.dy
        start.z -= self.dz

        return start

    def get_end(self, start: Point):
        end = Point(start.x, start.y, start.z)
        end.x += self.dx
        end.y += self.dy
        end.z += self.dz

        return end

    def copy(self):
        new = Vector();
        new.dx = self.dx;
        new.dy = self.dy;
        new.dz = self.dz;

        return new;

class Circle:
    def __init__(self):
        self.center: Point = Point(0, 0, 0)
        self.radius = 0

    def init_by_dots(self, point1: Point, point2: Point, point3: Point):
        vectors = [Vector() for i in range(3)]
        vectors[0].init_points(point1, point2)
        vectors[1].init_points(point2, point3)
        vectors[2].init_points(point1, point3)

        square = (vectors[0] * vectors[2]).length() / 2

        if (CALC_EPS > abs(square)):
            return None

        lengths = [side.length() for side in vectors]
        product = lengths[0] * lengths[1] * lengths[2]
        radius = product / 4 / square

        middle = point1.get_middle(point2)
        normal = vectors[0].copy()
        normal.normalize()
        normal = normal.get_normalXY()
        new_length = radius ** 2 - (lengths[0] / 2) ** 2

        if (CALC_EPS > abs(new_length)):
            new_length = 0

        normal.adjust(new_length ** 0.5)
        center = normal.get_end(middle)
        self.radius = radius

        if (CALC_EPS > abs(get_distance(center, point3) - radius)):
            self.center = center
            return self

        normal.adjust(-1)
        center = normal.get_end(middle)
        self.center = center

        return self

    def get_position(self, point: Point):
        value = (self.center.x - point.x) ** 2 \
                + (self.center.y - point.y) ** 2 \
                - self.radius ** 2

        if (CALC_EPS > abs(value)):
            return 0

        return value

    def get_tangent_points(self, point):
        distance = self.get_position(point)

        if (0 > distance):
            return []
        elif (0 == distance):
            return [point.copy()]

        points = []
        to_center = Vector().init_points(point, self.center);

        distance_to_center = to_center.length();

        normal = to_center.get_normalXY()
        normal_length = self.radius \
                        * (1 - (self.radius / distance_to_center) ** 2) ** 0.5
        distance_to_normal = distance_to_center \
                             - (self.radius ** 2) / distance_to_center
        normal.adjust(normal_length / normal.length())
        to_center.adjust(distance_to_normal / distance_to_center)
        base = to_center.get_end(point)

        points.append(normal.get_end(base))
        normal.adjust(-1)
        points.append(normal.get_end(base))

        return points;


def triangle_find_tangent_circles(triangle_points, points):
    if 3 != len(triangle_points):
        return None

    if 3 > len(triangle_points):
        return None

    out = []
    limit = len(points)

    for i in range(limit - 2):
        for j in range(i + 1, limit - 1):
            for k in range(j + 1, limit):
                circle = Circle()
                is_correct = circle.init_by_dots(points[i], 
                                                 points[j], 
                                                 points[k])

                if None is not is_correct:
                    tangent_points = \
                    triangle_get_tangent_point_circle(triangle_points, circle)

                    for point in tangent_points:
                        if (not _is_tangent_in_list(out, [circle, point[0], 
                                                          point[1], point[2]])):
                            out.append([circle, point[0], point[1], point[2]])

    return out

def _is_tangent_in_list(tangents, new):
    is_in = False

    i = 0
    limit = len(tangents)
    while limit > i and not is_in:
        current = tangents[i]

        if (CALC_EPS > abs(current[0].center.x - new[0].center.x)
            and CALC_EPS > abs(current[0].center.y - new[0].center.y)
            and CALC_EPS > abs(current[0].center.z - new[0].center.z)
            and CALC_EPS > abs(current[0].radius - new[0].radius)
            and CALC_EPS > abs(current[1].x - new[1].x)
            and CALC_EPS > abs(current[1].y - new[1].y)
            and CALC_EPS > abs(current[1].z - new[1].z)
            and ((current[2] == new[2] and current[3] == new[3])
                 or (current[2] == new[3] and current[3] == new[2]))):
            is_in = True

        i += 1

    return is_in

def triangle_get_tangent_point_circle(triangle_points, circle):
    out = []
    tangent_point = None

    i = 0
    j = 0
    while 3 > i:

        j = 0
        while 3 > j:
            if (i != j):
                tangent_point = \
                circle_get_tangent_point_vector(triangle_points[i],
                                                triangle_points[j],
                                                circle)

                if (None is not tangent_point):
                    out.append([tangent_point, i, j])

            j += 1

        i += 1

    return out

def find_biggest_square_task(triangle_points, points, circles_and_misc=None):
    if 3 != len(triangle_points):
        return None

    if 3 > len(triangle_points):
        return None

    if (None is circles_and_misc):
        circles_and_misc = triangle_find_tangent_circles(triangle_points, 
                                                         points)

    triangle_center = triangle_find_center(*triangle_points)
    biggest_circle = None
    biggest_square = 0
    triangle_side = None
    tangent_point = None

    for circle, point, triangle_i, triangle_j in circles_and_misc:
        square = triangle_get_square(circle.center, point, triangle_center)

        if CALC_EPS < abs(square) and biggest_square < square:
            biggest_square = square
            biggest_circle = circle
            triangle_side = [triangle_i, triangle_j]
            tangent_point = point

    return biggest_circle, biggest_square, triangle_center, \
           triangle_side, tangent_point

def circle_get_tangent_point_vector(point1, point2, circle):
    vector = Vector().init_points(point1, point2)
    tangent_points = circle.get_tangent_points(point1)
    tangent_vectors = [Vector().init_points(point1, point) for point 
                       in tangent_points]

    for i, v in enumerate(tangent_vectors):
        if vector.is_collinear(v):
            return tangent_points[i]

    return None

def triangle_find_center(point1: Point, point2: Point, point3: Point):
    side1 = Vector().init_points(point1, point2)
    side2 = Vector().init_points(point1, point3)

    median = side1 + side2
    median.adjust(1 / 3)

    return median.get_end(point1)

def tangent_circle_count_unique(circle_data):
    unique = []

    for i in range(len(circle_data)):
        j = 0
        mark = True

        while i > j and mark:
            if unique[j]:
                if (CALC_EPS > abs(circle_data[i][0].center.x - circle_data[j][0].center.x)
                    and CALC_EPS > abs(circle_data[i][0].center.y - circle_data[j][0].center.y)
                    and CALC_EPS > abs(circle_data[i][0].center.z - circle_data[j][0].center.z)
                    and CALC_EPS > abs(circle_data[i][0].radius - circle_data[j][0].radius)):
                    mark = False

            j += 1

        unique.append(mark)

    return unique.count(True)


def triangle_get_square(point1, point2, point3):
    vector1 = Vector()
    vector1.init_points(point1, point2)
    vector2 = Vector()
    vector2.init_points(point1, point3)

    return (vector1 * vector2).length() / 2


if __name__ == "__main__":
    tr = [Point(1, 0, 0), Point(2, 1, 0), Point(3, 0, 0)]
    dots = [Point(2, 2, 0), Point(2, 1.5, 0), Point(0, 0, 0), Point(2.5, 2, 0), 
            Point(2, 4, 0), Point(1, 2, 0), Point(3, 3, 0)]

    find_biggest_square_task(tr, dots)

