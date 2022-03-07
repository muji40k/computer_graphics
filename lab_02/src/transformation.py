import math


def point_move(point: list[float], movement: list[float]) -> None:
    for i in range(2):
        point[i] += movement[i]

def point_rotate(point: list[float], center: list[float], angle: float) -> None:
    angle = math.pi * angle / 180
    sin = math.sin(angle)
    cos = math.cos(angle)
    copy = [point[i] - center[i] for i in range(2)]

    point[0] = copy[0] * cos - copy[1] * sin + center[0]
    point[1] = copy[0] * sin + copy[1] * cos + center[1]

def point_scale(point: list[float], center: list[float], k: list[float]) -> None:
    for i in range(2):
        point[i] = k[i] * (point[i] - center[i]) + center[i]


