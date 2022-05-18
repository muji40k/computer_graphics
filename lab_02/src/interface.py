import math
import tkinter as tk
import tkinter.font
import src.transformation as transformation


OK                     = 0
FAILURE                = 1
ERROR_NON_EMPTY        = 2
ERROR_NON_DOUBLE_INPUT = 3
ERROR_EMPTY_INPUT      = 4


class Ui(tk.Tk):
    _default_size = (1200, 600)
    _text_header = "Лабораторная работа №2"

    _text_frame_move = "Перенос"
    _text_frame_scale = "Масштаб"
    _text_frame_rotate = "Поворот"

    _text_lable_task = "Программа, выполняющая преобразования\nна плоскости"
    _text_label_current_dot = "Введите координаты центра преобразования"
    _text_label_move = "Укажите новое положение центра преобразования"
    _text_label_scale = "Укажите коэффициенты масштабирования\nпо каждой из осей"
    _text_label_rotate = "Укажите угол поворота\n(отрицательный - " \
                         + "по часовой стрелке,\nположительный - против)"
    _text_label_log = "Информация"

    _text_success = "Преобразование выполнено успешно"
    _text_undo = "Возврат выполнен успешно"
    _text_reset = "Изменения сброшены"

    _text_error_header = "Ошибка:\n"
    _text_error_place = "Место ошибки: {}\n"

    _text_error_empty = "Ввод не может быть пустым\n"

    _text_error_input_cords = "Координаты точки задаются целыми " \
                              + "числами\n"
    _text_error_input_scales = "Коэффициенты масштабирования задаются " \
                               + "вещественными числами\n"
    _text_error_input_rotate = "Угол поворота задается вещественным числом\n"

    _text_errors_input = []

    for text in (_text_error_input_cords,
                 _text_error_input_scales,
                 _text_error_input_rotate):
        _text_errors_input.append(_text_error_header + text + _text_error_place)

    _text_error_place_current = "Координата центра {}"
    _text_error_place_cord = "Координата переноса {}"
    _text_error_place_scale = "Коэффициент масштабирования k{}"
    _text_error_place_angle = "Угол"

    _text_error_places = [_text_error_place_cord, _text_error_place_scale,
                          _text_error_place_angle]

    _text_cords = ("X", "Y")

    _text_button_proceed = "Преобразовать"
    _text_button_undo = "Отменить"

    _command_move   = 0;
    _command_scale  = 1;
    _command_rotate = 2;

    _dot_size = 5

    def __init__(self):
        super().__init__()

# Variables

        self.command_stack = []
        self.figure = []
        self.chosen_transform = tk.IntVar(value=self._command_move)

        self.string_vars_current_dot = [tk.StringVar(value="0") 
                                        for i in range(2)]
        self.string_vars_move = [tk.StringVar(value="0") 
                                 for i in range(2)]

# Frames

        # Left side
        self.frame_configure = tk.Frame(self)

        self.frame_current_dot = tk.Frame(self.frame_configure)
        self.frame_current_dot_entries = tk.Frame(self.frame_current_dot)

        self.frame_move = tk.LabelFrame(self.frame_configure, 
                                        text=self._text_frame_move,
                                        font=tkinter.font.BOLD)
        self.frame_move_entries = tk.Frame(self.frame_move)

        self.frame_scale = tk.LabelFrame(self.frame_configure, 
                                         text=self._text_frame_scale,
                                         font=tkinter.font.BOLD)
        self.frame_scale_entries = tk.Frame(self.frame_scale)

        self.frame_rotate = tk.LabelFrame(self.frame_configure, 
                                          text=self._text_frame_rotate,
                                          font=tkinter.font.BOLD)
        self.frame_rotate_entries = tk.Frame(self.frame_rotate)

        self.frame_buttons = tk.Frame(self.frame_configure)

        # Right side
        self.frame_result = tk.Frame(self)
        self.frame_log = tk.LabelFrame(self.frame_result,
                                       text=self._text_label_log,
                                       font=tkinter.font.BOLD)

# Widgets

        self.label_task = tk.Label(self.frame_configure,
                                   text=self._text_lable_task,
                                   font=tkinter.font.BOLD)
        # Current dot frame
        self.label_current_dot = tk.Label(self.frame_current_dot, 
                                          text=self._text_label_current_dot,
                                          justify="center")
        self.entries_current_dot = [tk.Entry(self.frame_current_dot_entries,
                                             justify="center",
                                             textvariable=self.string_vars_current_dot[i]
                                             ) for i in range(2)]

        # Move frame

        self.radio_move = tk.Radiobutton(self.frame_move, 
                                         text=self._text_label_move,
                                         justify="left",
                                         variable=self.chosen_transform,
                                         value=self._command_move,
                                         activebackground=self.cget('bg'))
        self.entries_move = [tk.Entry(self.frame_move_entries,
                                      justify="center",
                                      textvariable=self.string_vars_move[i]) 
                             for i in range(2)]

        # Scale frame

        self.radio_scale = tk.Radiobutton(self.frame_scale, 
                                          text=self._text_label_scale,
                                          justify="left",
                                          variable=self.chosen_transform,
                                          value=self._command_scale,
                                          activebackground=self.cget('bg'))
        self.entries_scale = [tk.Entry(self.frame_scale_entries,
                                             justify="center") for i 
                                    in range(2)]

        for entry in self.entries_scale:
            entry.insert(0, "1")

        # Rotate frame

        self.radio_rotate = tk.Radiobutton(self.frame_rotate, 
                                           text=self._text_label_rotate,
                                           justify="left",
                                           variable=self.chosen_transform,
                                           value=self._command_rotate,
                                           activebackground=self.cget('bg'))
        self.entries_rotate = [tk.Entry(self.frame_rotate_entries,
                                             justify="center") for i 
                                    in range(1)]

        for entry in self.entries_rotate:
            entry.insert(0, "0")

        # Buttons

        self.button_proceed = tk.Button(self.frame_buttons, 
                                        text=self._text_button_proceed)
        self.button_undo = tk.Button(self.frame_buttons,
                                     text=self._text_button_undo,
                                     state=tk.DISABLED)

        # Result side

        self.canvas = tk.Canvas(self.frame_result, bg="#fff")
        self.console = tk.Text(self.frame_log, height=3, state=tk.DISABLED)

        # Canvas

        self.dot_center = None
        self.dot_move_center = None
# Misc

        self.conf_amount = 3
        self.frames_configure = [self.frame_move, 
                                 self.frame_scale, 
                                 self.frame_rotate]
        self.frames_entiries = [self.frame_move_entries, 
                                self.frame_scale_entries, 
                                self.frame_rotate_entries]
        self.conf_radios = [self.radio_move, 
                            self.radio_scale, 
                            self.radio_rotate]
        self.conf_entries = [self.entries_move, 
                             self.entries_scale, 
                             self.entries_rotate]

# Binds

        self.button_proceed.bind("<Button-1>", 
                                 lambda event: self.on_press_proceed())

        self.button_undo.bind("<Button-1>", 
                              lambda event: self.on_press_undo())

        self.button_undo.bind("<Button-3>", 
                              lambda event: self.on_press_reset())

        self.canvas.bind("<Configure>", lambda event: self.build_canvas())

        self.frame_move.bind("<Button-1>", 
                             lambda event: self.radio_move.select())
        self.frame_scale.bind("<Button-1>", 
                             lambda event: self.radio_scale.select())
        self.frame_rotate.bind("<Button-1>", 
                             lambda event: self.radio_rotate.select())

        for child in self.frame_move.winfo_children():
            child.bind("<Button-1>", lambda event: self.radio_move.select())

        for child in self.frame_scale.winfo_children():
            child.bind("<Button-1>", lambda event: self.radio_scale.select())

        for child in self.frame_rotate.winfo_children():
            child.bind("<Button-1>", lambda event: self.radio_rotate.select())

        for entry in self.entries_move:
            entry.bind("<Button-1>", lambda event: self.radio_move.select())

        for entry in self.entries_scale:
            entry.bind("<Button-1>", lambda event: self.radio_scale.select())

        for entry in self.entries_rotate:
            entry.bind("<Button-1>", lambda event: self.radio_rotate.select())

        self.canvas.bind("<Button-1>", 
                         lambda event: 
                         self.on_mouse_center(event, self.entries_current_dot))

        self.canvas.bind("<Button-3>", 
                         lambda event: 
                         self.on_mouse_center(event, self.entries_move))

        for string_var in self.string_vars_current_dot + self.string_vars_move:
            string_var.trace("w", lambda name, index, mode: self.draw_dot())

        self.chosen_transform.trace("w", 
                                    lambda name, index, mode: 
                                    self.draw_dot())

        self._setup_ui()
        self.reset_figure()
        self.build_canvas()

    def _setup_ui(self):
        self.title(self._text_header)
        self.geometry("{}x{}+50+50".format(*self._default_size))

    # Main frame
        self.columnconfigure(1, weight=1)
        self.rowconfigure(0, weight=1)

        self.frame_configure.grid(row=0, column=0, sticky="wsne")
        self.frame_result.grid(row=0, column=1, sticky="wsne")

    # Configure frame
        self.frame_configure.columnconfigure(0, weight=1)

        self.frame_configure.rowconfigure(1, weight=1)
        for i in range(2, 2 + self.conf_amount):
            self.frame_configure.rowconfigure(i, weight=1)

        self.frame_configure.grid(row=0, column=0, sticky="wsne")
        self.frame_configure.columnconfigure(0, weight=1)

        self.label_task.grid(row=0, column=0, sticky="wsne")
        self.frame_current_dot.grid(row=1, column=0)#, sticky="wsne")
        self.frame_current_dot.columnconfigure(0, weight=1)
        self.label_current_dot.grid(row=0, column=0, sticky="wsne")
        self.frame_current_dot_entries.grid(row=1, column=0, sticky="wsne")

        for i, entry in enumerate(self.entries_current_dot):
            entry.grid(row=0, column=i, sticky="wsne")

        self.frame_buttons.grid(row=5, column=0, sticky="wsne")
        self.frame_buttons.rowconfigure(0, weight=1)
        self.frame_buttons.columnconfigure(0, weight=1)
        self.frame_buttons.columnconfigure(1, weight=1)
        self.button_proceed.grid(row=0, column=1, sticky="wsne")
        self.button_undo.grid(row=0, column=0, sticky="wsne")

    # Configure trasformations

        for i in range(self.conf_amount):
            self.frames_configure[i].grid(row=i + 2, column=0, sticky="wsne")
            self.frames_configure[i].columnconfigure(0, weight=1)
            self.frames_configure[i].rowconfigure(0, weight=1)
            self.conf_radios[i].grid(row=0, column=0, sticky="wsn")
            self.frames_entiries[i].grid(row=1, column=0)#, sticky="wsne")

            for entries in self.conf_entries:
                for j, entry in enumerate(entries):
                    self.frames_entiries[i].columnconfigure(j, weight=1)
                    entry.grid(row=0, column=j, sticky="wsne")

    # Result frame

        self.frame_result.grid(row=0, column=1, sticky="wsne")
        self.frame_result.columnconfigure(0, weight=1)
        self.frame_result.rowconfigure(0, weight=1)

        self.canvas.grid(row=0, column=0, sticky="wsne")
        self.frame_log.grid(row=1, column=0, sticky="wsne")

        self.frame_log.columnconfigure(0, weight=1)
        self.frame_log.rowconfigure(0, weight=1)

        self.console.grid(row=0, column=0, sticky="wsne")

    def write_message(self, msg):
        self.console.configure(state=tk.NORMAL)
        self.console.delete(0.0, tk.END)
        self.console.insert(0.0, msg)
        self.console.configure(state=tk.DISABLED)

    def reset_figure(self):
        self.figure = _create_cat(self._default_size[1] * 0.5)

    def apply_transform(self, all=False):
        start = 0 if all else len(self.command_stack) - 1

        for command in self.command_stack[start:]:
            for figure in self.figure:
                for i in range(len(figure)):
                    if (self._command_move == command[0]):
                        transformation.point_move(figure[i], *command[1])
                    elif (self._command_scale == command[0]):
                        transformation.point_scale(figure[i], *command[1])
                    elif (self._command_rotate == command[0]):
                        transformation.point_rotate(figure[i], *command[1])

    def build_canvas(self):
        self.canvas.unbind("<Configure>")
        self.canvas.delete("all")
        self.dot_center = None
        self.dot_move_center = None

        width = self.canvas.winfo_width()
        height = self.canvas.winfo_height()

        self.canvas.create_line([0, height // 2, width, height // 2], 
                                fill="#C3C3C3")
        self.canvas.create_line([width // 2, 0, width // 2, height], 
                                fill="#C3C3C3")

        self.draw_figure(width, height)
        self.draw_dot(width, height)

        self.canvas.bind("<Configure>", lambda event: self.build_canvas())

    def draw_dot(self, width=None, height=None):
        if (None is width or None is height):
            width = self.canvas.winfo_width()
            height = self.canvas.winfo_height()

        buffer = []
        center = [[], []]

        if (None is not self.dot_center):
            self.canvas.delete(self.dot_center)
            self.dot_center = None

        if (None is not self.dot_move_center):
            self.canvas.delete(self.dot_move_center)
            self.dot_move_center = None

        rc = _get_input_from_entries(self.entries_current_dot, buffer)

        if (OK == rc):
            rc = _input_to_type(buffer, center[0], int)

        if (OK == rc):
            transformation.point_scale(center[0], [0, 0], [1, -1])
            transformation.point_move(center[0], [width // 2, height // 2])

            self.dot_center = \
            self.canvas.create_oval([center[0][i] - (1 - 2 * j) * self._dot_size
                                     for j in range(2) for i in range(2)],
                                     fill="#000")

        buffer.clear()

        if (self._command_move == self.chosen_transform.get()):
            rc = _get_input_from_entries(self.entries_move, buffer)

            if (OK == rc):
                rc = _input_to_type(buffer, center[1], int)

            if (OK == rc):
                transformation.point_scale(center[1], [0, 0], [1, -1])
                transformation.point_move(center[1], [width // 2, height // 2])

                self.dot_move_center = \
                self.canvas.create_oval([center[1][i] 
                                         - (1 - 2 * j) * self._dot_size
                                         for j in range(2) for i in range(2)],
                                         outline="#FFD000",
                                         fill="#FFD000")

            buffer.clear()

    def draw_figure(self, width, height):
        for figure in self.figure:
            current = [figure[0][0] + width // 2, -figure[0][1] + height // 2]

            for dot in figure[1:]:
                dot = [dot[0] + width // 2, -dot[1] + height // 2]
                self.canvas.create_line(current + dot)
                current = dot.copy()

    def add_command(self, center, data):
        new = [self.chosen_transform.get(), []]

        if (self._command_move == self.chosen_transform.get()):
            new[1] = [[data[i] - center[i] for i in range(2)]]
        elif (self._command_scale == self.chosen_transform.get()):
            new[1] = [center.copy(), data.copy()]
        elif (self._command_rotate == self.chosen_transform.get()):
            new[1] = [center.copy(), data[0]]

        self.command_stack.append(new)

    def on_mouse_center(self, event, entries):
        if (self._command_move != self.chosen_transform.get()
            and self.entries_move == entries):
            return

        width = self.canvas.winfo_width()
        height = self.canvas.winfo_height()

        point = [event.x, event.y]
        transformation.point_move(point, [-(width // 2), -(height // 2)])
        transformation.point_scale(point, [0, 0], [1, -1])

        for i in range(2):
            entries[i].delete(0, tk.END)
            entries[i].insert(0, str(point[i]))

        self.draw_dot()

    def on_press_proceed(self):
        self.write_message("")
        buffer = []
        center = []
        input_data = []

        rc = _get_input_from_entries(self.entries_current_dot, buffer)

        if (ERROR_EMPTY_INPUT == rc):
            self.write_message((self._text_error_header 
                                + self._text_error_empty
                                + self._text_error_place)
                                .format(self._text_error_place_current
                                        .format(self._text_cords[len(buffer)])))
            rc = FAILURE

        if (OK == rc):
            rc = _input_to_type(buffer, center, int)

        if (ERROR_NON_DOUBLE_INPUT == rc):
            self.write_message((self._text_error_header 
                                + self._text_error_input_cords
                                + self._text_error_place)
                                .format(self._text_error_place_current
                                        .format(self._text_cords[len(center)])))
            rc = FAILURE

        if (OK == rc):
            buffer.clear()
            rc = \
            _get_input_from_entries(self.conf_entries[self.chosen_transform.get()], 
                                    buffer)

        if (ERROR_EMPTY_INPUT == rc):
            self.write_message((self._text_error_header 
                                + self._text_error_empty
                                + self._text_error_place)
                                .format(self._text_error_places[self.chosen_transform.get()]
                                        .format(self._text_cords[len(buffer)])))
            rc = FAILURE

        if (OK == rc):
            rc = _input_to_type(buffer, input_data, int 
                                if self._command_move == self.chosen_transform.get() 
                                else float)

        if (ERROR_NON_DOUBLE_INPUT == rc):
            self.write_message(self._text_errors_input[self.chosen_transform.get()]
                               .format(self._text_error_places[self.chosen_transform.get()]
                                       .format(self._text_cords[len(input_data)])))
            rc = FAILURE

        if (OK == rc):
            self.add_command(center, input_data)

        if (OK == rc):
            self.write_message(self._text_success)
            self.button_undo.configure(state=tk.NORMAL)
            self.apply_transform()
            self.build_canvas()

    def on_press_undo(self):
        if (0 == len(self.command_stack)):
            self.button_undo.configure(state=tk.DISABLED)
            return

        self.write_message(self._text_undo)

        if (1 == len(self.command_stack)):
            self.button_undo.configure(state=tk.DISABLED)

        if (self._command_scale == self.command_stack[-1][0]
            and 0 in self.command_stack[-1][1][1]):
            del self.command_stack[-1]
            self.reset_figure()
            self.apply_transform(True)
            self.build_canvas()
            return

        if (self._command_move == self.command_stack[-1][0]):
            self.command_stack[-1][1][0] = \
                    [-i for i in self.command_stack[-1][1][0]]
        elif (self._command_scale == self.command_stack[-1][0]):
            self.command_stack[-1][1][1] = \
                    [1 / i for i in self.command_stack[-1][1][1]]
        elif (self._command_rotate == self.command_stack[-1][0]):
            self.command_stack[-1][1][1] = -self.command_stack[-1][1][1]

        self.apply_transform()
        del self.command_stack[-1]
        self.build_canvas()

    def on_press_reset(self):
        self.write_message(self._text_reset)
        self.button_undo.configure(state=tk.DISABLED)
        self.command_stack.clear()
        self.reset_figure()
        self.build_canvas()


def _get_input_from_entries(entries: list[tk.Entry], out: list[str]) -> int:
    if (0 != len(out)):
        return ERROR_NON_EMPTY

    for entry in entries:
        tmp = entry.get().strip()

        if "" == tmp:
            return ERROR_EMPTY_INPUT

        out.append(tmp)

    return OK

def _input_to_type(input_values: list[str], out: list[float], func) -> int:
    if (0 != len(out)):
        return ERROR_NON_EMPTY

    for value in input_values:
        try:
            tmp = func(value)
            out.append(tmp)
        except ValueError:
            return ERROR_NON_DOUBLE_INPUT

    return OK

def _create_ellipse(a: float, b: float) -> list[list[float]]:
    step = 1 / max(a, b)
    angle = 0
    out = []

    while (2 * math.pi > angle):
        out.append([round(a * math.cos(angle), 0), 
                    round(b * math.sin(angle), 0)])

        angle += step

    out.append([round(a, 0), 0])

    return out

def _create_cat(height):
    body_size = [height / 5, height / 2.5]
    body_size = [i - i % 50 for i in body_size]
    head_size = body_size[0] * 0.8
    eye_size = head_size / 5
    eye_offset = (head_size - eye_size) / 2
    mustache_size = body_size[0]
    mustache_offset = head_size / 6

# Head
    head = _create_ellipse(head_size, head_size)

    ear_right = [[head_size * math.cos(math.pi / 6), 
                  head_size * math.sin(math.pi / 6)],
                 [1.5 * head_size * math.cos(math.pi / 4), 
                  1.5 * head_size * math.sin(math.pi / 4)],
                 [head_size * math.cos(math.pi / 3), 
                  head_size * math.sin(math.pi / 3)]]

    ear_left = [i.copy() for i in ear_right]

    for point in ear_left:
        transformation.point_scale(point, [0, 0], [-1, 1])

    eye_right = _create_ellipse(eye_size, eye_size)
    eye_left = [i.copy() for i in eye_right]

    for point in eye_right:
        transformation.point_move(point, [eye_offset, eye_offset])

    for point in eye_left:
        transformation.point_move(point, [-eye_offset, eye_offset])

    mustache_straight = [[-mustache_size, 0], [mustache_size, 0]]
    mustache_angle_start = [mustache_size * math.cos(math.pi / 8),
                            mustache_size * math.sin(math.pi / 8)]
    mustache_angle_end = mustache_angle_start.copy()
    transformation.point_scale(mustache_angle_end, [0, 0], [-1, -1])

    mustache_right = [mustache_angle_start, mustache_angle_end]
    mustache_left = [i.copy() for i in mustache_right]

    for point in mustache_left:
        transformation.point_scale(point, [0, 0], [-1, 1])

    for point in mustache_left + mustache_right + mustache_straight:
        transformation.point_move(point, [0, -mustache_offset])

    for point in head + ear_right + ear_left + eye_right + eye_left \
                 + mustache_straight + mustache_right + mustache_left:
        transformation.point_move(point, [0, body_size[1] + head_size])
# Body
    body = _create_ellipse(*body_size)

    return [head, ear_right, ear_left, eye_right, eye_left, 
            mustache_straight, mustache_right, mustache_left, body]

