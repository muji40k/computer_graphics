import tkinter as tk


class Drawer():
    _eps = 1e-8
    _default_width = 1
    _default_height = 1
    _default_dot = 10
    _default_line_width = 3
    _margin = 2 * _default_dot
    _default_view_area_X = 0.8
    _default_view_area_Y = 0.8

    def __init__(self, canvas: tk.Canvas):
        self.target = canvas
        self.frame = None
        self.reset_frame()

    def clear(self):
        self.target.delete("all")

    def reset_frame(self):
        self.rect = [[None, None], [None, None]]

    def update_frame(self, points):
        self.reset_frame()
        self.extend_frame(points)

    def extend_frame(self, points):
        for dot in points:
            for i in range(2):
                for j in range(2):
                    if (None is self.rect[i][j] 
                        or (1 - 2 * (i % 2)) * dot[j] 
                           <= (1 - 2 * (i % 2)) * self.rect[i][j]):
                        self.rect[i][j] = dot[j]

    def adjust_point(self, center_screen, center_plot, scales, dot):
        moved = [dot[i] - center_plot[i] for i in range(2)]
        return [int(scales[i] * moved[i] + center_screen[i]) 
                if None is not scales[i] else int(moved[i] + center_screen[i])
                for i in range(2)]


    def get_axes(self, is_equal=True):
        width = self.target.winfo_width()
        height = self.target.winfo_height()
        width_plot = self.rect[1][0] - self.rect[0][0]
        height_plot = self.rect[1][1] - self.rect[0][1]

        center_screen = [width / 2, height / 2]
        center_plot = [self.rect[0][0] + width_plot / 2, 
                       self.rect[0][1] + height_plot / 2]

        scales = [(dimension[0] - 2 * self._margin) / dimension[1]
                  if self._eps < abs(dimension[1]) else None
                  for dimension in [[width, width_plot], [height, height_plot]]]

        if (is_equal and None not in scales):
            min_ = min(scales)
            scales = [min_, min_]

        if (None is not scales[1]):
            scales[1] *= -1

        return center_screen, center_plot, scales


    def draw_points(self, points, is_equal=True, **kwargs):
        if (0 == len(points)):
            return

        if None in self.rect[0] or None in self.rect[1]:
            self.update_frame(points)

        center_screen, center_plot, scales = self.get_axes(is_equal=is_equal)

        for dot in points:
            cur = self.adjust_point(center_screen, center_plot, scales, dot)
            self.target.create_oval([cur[j] 
                                     - (1 - 2 * (i % 2)) * self._default_dot
                                     for i in range(2) for j in range(2)],
                                    kwargs)

    def draw_curve(self, points, is_equal=True, is_closed=True, **kwargs):
        if (0 == len(points)):
            return

        if None in self.rect[0] or None in self.rect[1]:
            self.update_frame(points)

        center_screen, center_plot, scales = self.get_axes(is_equal=is_equal)

        i = 1
        limit = len(points)
        current = []
        next = self.adjust_point(center_screen, center_plot, scales, points[0])
        first = next.copy()

        while limit > i:
            current = next
            next = self.adjust_point(center_screen, center_plot, 
                                    scales, points[i])

            self.target.create_line(*(current + next), kwargs, 
                                    width=self._default_line_width)

            i += 1

        if is_closed:
            self.target.create_line(*(next + first), kwargs, 
                                    width=self._default_line_width)

    def draw_circle(self, center, radius, is_equal=True, **kwargs):
        if (2 != len(center) or 0 > radius):
            return

        if None in self.rect[0] or None in self.rect[1]:
            self.update_frame([[center[0] + radius, center[1] + radius], 
                               [center[0] - radius, center[1] - radius]])

        center_screen, center_plot, scales = self.get_axes(is_equal=is_equal)
        left = self.adjust_point(center_screen, center_plot, scales, 
                                 [center[0] + radius, center[1] + radius])
        right = self.adjust_point(center_screen, center_plot, scales, 
                                  [center[0] - radius, center[1] - radius])

        self.target.create_oval(*(left + right), kwargs, 
                                width=self._default_line_width)

    def draw_text(self, points, lables, is_equal=True, **kwargs):
        if (0 == len(points)):
            return

        if None in self.rect[0] or None in self.rect[1]:
            self.update_frame(points)

        center_screen, center_plot, scales = self.get_axes(is_equal=is_equal)

        for i in range(len(points)):
            cur = self.adjust_point(center_screen, center_plot, scales, points[i])
            self.target.create_text(cur[0], cur[1], kwargs, text=lables[i])

