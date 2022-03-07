import tkinter as tk
import tkinter.font
import calculation as calc

from drawer import Drawer

class Ui(tk.Tk):
    _bd_inner = 2
    _bd_outer = 1
    _default_size = (1280, 720)

    _text_task = "Программа,  находящая  треугольник  максимальной  площади,\n" \
               + "среди  треуольников,   образованных   центром  окружности,\n" \
               + "проходящей  хотя  бы  через  3  точки  заданного множества\n" \
               + "и касающейся хотя бы одной стороны заданного треугольника,\n" \
               + "его центром и точкой касания"

    _text_result = "Найдено касающихся окружностей: {}\n"                \
                    + "Окружность, образующая треугольник максимальной " \
                    + "площади: X = {:.7f}, Y = {:.7f}, R = {:.7f}, "    \
                    + "S = {:.7f}\n"                                     \
                    + "Задействованные точки: {:s}\n"                    \
                    + "Точка касания: X = {:.7f}, Y = {:.7f}\n"          \
                    + "Центр треугольника: X = {:.7f}, Y = {:.7f}"

    _text_error_header = "Ошибка:\n"
    _text_error_place = "Место ошибки: координата {} {}\n"
    _text_error_place_trianle = "вершины {} треугольника"
    _text_error_place_dot = "точки {} из множества"

    _text_error_non_float_cord = _text_error_header                         \
                                 + "Координата точки задается вещественным" \
                                 + " числом\n"                              \
                                 + _text_error_place
    _text_error_empty_input = _text_error_header          \
                              + "Координата не указана\n" \
                              + _text_error_place
    _text_error_no_circle = _text_error_header \
                            + "Не удалось найти не одной требуемой окружности\n"

    _text_incorrect_triangle = _text_error_header + "Треугольник вырожден"

    _text_not_enough_points = _text_error_header                               \
                              + "Введено недостаточно точек для построения "   \
                              + "хотя бы одной искомой окружности (минимум 3)"

    _text_header = "Лабораторная работа №1"
    _text_group_triangle = "Треугольник"
    _text_title_triangle = "Введите координаты вершин треугольника"
    _text_prompt_triangle = "Вершина {}"
    _text_group_dots = "Точки"
    _text_title_dots = "Введите координаты точек"
    _text_log = "Информация"
    _text_procced = "Найти"
    _text_is_all = "Построить все точки"
    _text_triangle_dots = ("A", "B", "C")
    _text_cords = ("X", "Y")
    _text_button_add = "Добавить"

    def __init__(self):
        super().__init__()

        # Variables
        self.dots = []
        self.selected_dots = []
        self.circle = None
        self.tangent_point = None
        self.triangle_side = None
        self.triangle_center = None
        self.triangle_dots = []
        self.is_set = False

        # Frames
        self.frame_configure = tk.Frame(self)
        self.frame_result = tk.Frame(self)
        self.group_triangle = tk.LabelFrame(self.frame_configure,
                                            text=self._text_group_triangle,
                                            font=tkinter.font.BOLD)
        self.group_dots = tk.LabelFrame(self.frame_configure, 
                                        text=self._text_group_dots,
                                        font=tkinter.font.BOLD)
        self.group_access = tk.Frame(self.frame_configure)

        # Labels
        self.title_task = tk.Label(self.frame_configure,
                                   text=self._text_task,
                                   justify="left")
        self.title_dots = tk.Label(self.group_dots,
                                   text=self._text_title_dots)
        self.title_triangle = tk.Label(self.group_triangle,
                                       text=self._text_title_triangle)

        # Triangle stuff
        self.inputs_triangle = []
        self.labels_triangle = []
        self.frames_input_triangle = []

        for i in range(len(self._text_triangle_dots)):
            current_frame = tk.Frame(self.group_triangle)
            self.frames_input_triangle.append(current_frame);
            self.inputs_triangle.append([tk.Entry(current_frame, justify="center"),
                                         tk.Entry(current_frame, justify="center")])
            self.labels_triangle.append(
                            tk.Label(current_frame,
                                     text=(self._text_prompt_triangle
                                           .format(self
                                                   ._text_triangle_dots[i]))))

        # List stuff
        self.list_frames = []
        self.group_dot_list_back = tk.Frame(self.group_dots)
        self.group_canvas_back = tk.Frame(self.group_dot_list_back, 
                                          bd=self._bd_inner, relief=tk.SUNKEN)
        self.canvas_list = tk.Canvas(self.group_canvas_back)
        self.group_dot_list = tk.Frame(self.canvas_list)
        self.scrollbar_dot_list = tk.Scrollbar(self.group_dot_list_back,
                                               orient=tk.VERTICAL,
                                               command=self.canvas_list.yview)

        # Buttons
        self.button_process = tk.Button(self.group_access, 
                                        text=self._text_procced)
        self.button_add = tk.Button(self.group_dot_list, 
                                    text=self._text_button_add,
                                    bd=self._bd_outer, relief=tk.RAISED)

        # CheckBoxes
        self.is_all = tk.BooleanVar(value=False)
        self.checkbox_is_all = tk.Checkbutton(self.group_access,
                                              text=self._text_is_all,
                                              variable=self.is_all,
                                              onvalue=True,
                                              offvalue=False)

        # Misc
        self.canvas = tk.Canvas(self.frame_result, bg="#fff")
        self.log_frame = tk.LabelFrame(self.frame_result, 
                                       text=self._text_log,
                                       font=tkinter.font.BOLD)
        self.log = tk.Text(self.log_frame, height=5, state=tk.DISABLED)
        self.drawer = Drawer(self.canvas)

        # Binds
        self.button_add.bind("<Button-1>", lambda event: self.on_add())
        self.button_process.bind("<Button-1>", lambda event: self.on_proceed())
        self.group_dot_list.bind("<Configure>", lambda event: 
                                 self.canvas_list.config(scrollregion = \
                                                         (self
                                                          .canvas_list
                                                          .bbox("all"))))
        self.button_add.bind("<Button-4>", lambda event: self.on_list_scroll(event))
        self.button_add.bind("<Button-5>", lambda event: self.on_list_scroll(event))
        self.canvas_list.bind("<Button-4>", lambda event: self.on_list_scroll(event))
        self.canvas_list.bind("<Button-5>", lambda event: self.on_list_scroll(event))
        self.canvas.bind("<Configure>", lambda event: self.draw_plot())

        self.init_ui()

    def init_ui(self):
        self.title(self._text_header)
        self.geometry("{}x{}+50+50".format(self._default_size[0], 
                                           self._default_size[1]))

        # Frame main
        self.rowconfigure(0, weight=1)
        self.columnconfigure(1, weight=1)
        self.frame_configure.grid(row=0, column=0, sticky="wsne")

        # Frame configure
        self.frame_configure.columnconfigure(0, weight=1)
        self.frame_configure.rowconfigure(2, weight=1)

        self.title_task.grid(row=0, column=0, sticky="wsne")

        # Triangle
        self.group_triangle.grid(row=1, column=0, sticky="wsne")
        self.group_triangle.columnconfigure(0, weight=1)
        self.title_triangle.grid(row=0, column=0, sticky="wsne")

        for i in range(len(self._text_triangle_dots)):
            self.frames_input_triangle[i].columnconfigure(1, weight=1)
            self.frames_input_triangle[i].columnconfigure(2, weight=1)
            self.frames_input_triangle[i].grid(row=1 + i, column=0, sticky="wsne")
            self.labels_triangle[i].grid(row=0, column=0, sticky="wsne");
            self.inputs_triangle[i][0].grid(row=0, column=1, sticky="wsne");
            self.inputs_triangle[i][1].grid(row=0, column=2, sticky="wsne");

        # Dots
        self.group_dots.grid(row=2, column=0, sticky="wsne")
        self.title_dots.grid(row=0, column=0, sticky="wsne")
        self.group_dots.rowconfigure(1, weight=1)

        # Dot list
        self.group_dot_list_back.grid(row=1, column=0, sticky="wsne")
        self.group_dot_list_back.columnconfigure(0, weight=1)
        self.group_dot_list_back.rowconfigure(0, weight=1)
        self.group_canvas_back.grid(row=0, column=0, sticky="wsne")
        self.group_canvas_back.rowconfigure(0, weight=1)
        self.canvas_list.grid(row=0, column=0, sticky="wsne")
        self.scrollbar_dot_list.grid(row=0, column=1, sticky="wsne")

        self.canvas_list.config(yscrollcommand=self.scrollbar_dot_list.set)

        # self.group_dot_list.columnconfigure(0, weight=1)
        self.build_list()

        # Process
        self.group_access.columnconfigure(0, weight=1)
        self.group_access.grid(row=3, column=0, sticky="wsne")

        self.button_process.grid(row=0, column=0, sticky="wsne")
        self.checkbox_is_all.grid(row=0, column=1, sticky="wsne")

        # Frame result
        self.frame_result.columnconfigure(0, weight=1)
        self.frame_result.rowconfigure(0, weight=1)
        self.frame_result.grid(row=0, column=1, sticky="wsne")

        self.canvas.grid(row=0, column=0, sticky="wsne")

        self.log_frame.grid(row=1, column=0, sticky="wsne")
        self.log.pack(fill=tk.BOTH)

    def build_list(self):
        width = self.canvas_list.winfo_reqwidth()

        self.canvas_list.delete("all")
        self.canvas_list.create_window((0, 0), 
                                        window=self.group_dot_list,
                                        anchor="nw", width=width)

        for i, item in enumerate(self.list_frames):
            item.update_index(i)
            item.pack(side=tk.TOP, fill=tk.X)

        self.button_add.pack(side=tk.BOTTOM, fill=tk.X)

    def write_log_msg(self, msg):
        self.log.configure(state=tk.NORMAL)
        self.log.delete(0.0, tk.END)
        self.log.insert(0.0, msg)
        self.log.configure(state=tk.DISABLED)

    def get_input(self):
        new_dots = []
        new_triangle = []
        msg = ""

        is_correct = True
        i = 0
        limit_triangle = len(self.inputs_triangle)
        limit_dots = len(self.list_frames)

        while limit_triangle > i and is_correct:
            j = 0
            new_triangle.append([])

            while 2 > j and is_correct:
                number = self.inputs_triangle[i][j].get()

                if "" == number:
                    is_correct = False
                    msg = (self._text_error_empty_input
                           .format(self._text_cords[j], 
                                   (self._text_error_place_trianle
                                    .format(self._text_triangle_dots[i]))))
                else:
                    try:
                        number = float(number)
                        new_triangle[-1].append(number)
                    except ValueError:
                        is_correct = False
                        msg = (self._text_error_non_float_cord
                               .format(self._text_cords[j], 
                                       (self._text_error_place_trianle
                                        .format(self._text_triangle_dots[i]))))

                j += 1

            i += 1

        i = 0

        while limit_dots > i and is_correct:
            j = 0
            new_dots.append([])
            current_input = self.list_frames[i].get_input()

            while 2 > j and is_correct:
                number = current_input[j]

                if "" == number:
                    is_correct = False
                    msg = (self._text_error_empty_input
                           .format(self._text_cords[j], 
                                   (self._text_error_place_dot
                                    .format(i + 1))))
                else:
                    try:
                        number = float(number)
                        new_dots[-1].append(number)
                    except ValueError:
                        is_correct = False
                        msg = (self._text_error_non_float_cord
                               .format(self._text_cords[j], 
                                       (self._text_error_place_dot
                                        .format(i + 1))))

                j += 1

            i += 1


        if is_correct:
            self.dots = new_dots
            self.triangle_dots = new_triangle
            self.selected_dots.clear()

        self.write_log_msg(msg)

        return is_correct

# Graphics

    def draw_plot(self):
        if not self.is_set:
            return

        selected_dots = [self.dots[i] for i in self.selected_dots]

        self.canvas.unbind("<Configure>")

        self.drawer.clear()
        self.drawer.update_frame(self.triangle_dots)
        self.drawer.extend_frame(selected_dots)

        if (self.is_all.get()):
            self.drawer.extend_frame(self.dots)

        if (None is not self.circle):
            self.drawer.extend_frame([[self.circle.center.x - self.circle.radius,
                                       self.circle.center.y - self.circle.radius],
                                      [self.circle.center.x + self.circle.radius,
                                       self.circle.center.y + self.circle.radius]])

        if (self.is_all.get()):
            self.drawer.draw_points(self.dots, fill="#ccc", outline="#ccc")

        if (None is not self.circle):
            self.drawer.draw_circle([self.circle.center.x, self.circle.center.y],
                                    self.circle.radius)

        self.drawer.draw_curve(self.triangle_dots, fill="#f00")
        self.drawer.draw_curve([[self.circle.center.x, self.circle.center.y],
                                [self.tangent_point.x, self.tangent_point.y],
                                [self.triangle_center.x, self.triangle_center.y]
                                ], fill="#FFCD00")

        side = [self.triangle_dots[i] for i in self.triangle_side]

        if (calc.CALC_EPS > abs(side[0][0] - side[1][0])):
            side.sort(key=lambda x: x[1])

            if (self.tangent_point.y <= side[0][1] + calc.CALC_EPS):
                self.drawer.draw_curve([[self.tangent_point.x, self.tangent_point.y],
                                        side[0]], is_closed=False,
                                        dash=(5, 5), fill="#54FF00")
            elif (self.tangent_point.y >= side[1][1] - calc.CALC_EPS):
                self.drawer.draw_curve([[self.tangent_point.x, self.tangent_point.y],
                                        side[1]], is_closed=False,
                                        dash=(5, 5), fill="#54FF00")
        else:
            side.sort(key=lambda x: x[0])

            if (self.tangent_point.x <= side[0][0] + calc.CALC_EPS):
                self.drawer.draw_curve([[self.tangent_point.x, self.tangent_point.y],
                                        side[0]], is_closed=False,
                                        dash=(5, 5), fill="#54FF00")
            elif (self.tangent_point.x >= side[1][0] - calc.CALC_EPS):
                self.drawer.draw_curve([[self.tangent_point.x, self.tangent_point.y],
                                        side[1]], is_closed=False,
                                        dash=(5, 5), fill="#54FF00")

        self.drawer.draw_points(self.triangle_dots, fill="#f00", outline="#f00")
        self.drawer.draw_points(selected_dots, fill="#00f", outline="#00f")
        self.drawer.draw_points([[dot.x, dot.y] for dot in (self.circle.center, 
                                                            self.triangle_center)], 
                                fill="#FFCD00", outline="#FFCD00")
        self.drawer.draw_points([[self.tangent_point.x, self.tangent_point.y]],
                                fill="#54FF00", outline="#54FF00")

        font = tkinter.font.Font(font=tkinter.font.NORMAL)
        font.configure(size=14)
        self.drawer.draw_text(selected_dots, 
                              [str(i + 1) for i in self.selected_dots],
                              fill="#BDBDFF", font=font)
        self.drawer.draw_text(self.triangle_dots, self._text_triangle_dots,
                              fill="#FFB9B9", font=font)

        self.canvas.bind("<Configure>", lambda event: self.draw_plot())

# Handlers 

    def on_add(self):
        self.list_frames.append(Ui_list_item(self.group_dot_list, 
                                             len(self.list_frames),
                                             self.on_delete))

        self.list_frames[-1].bind("<Button-4>", 
                                  lambda event: self.on_list_scroll(event))
        self.list_frames[-1].bind("<Button-5>", 
                                  lambda event: self.on_list_scroll(event))

        for item in self.list_frames[-1].winfo_children():
            item.bind("<Button-4>", lambda event: self.on_list_scroll(event))
            item.bind("<Button-5>", lambda event: self.on_list_scroll(event))

        self.list_frames[-1].pack(side=tk.TOP, fill=tk.X)

    def on_delete(self, index):
        self.list_frames[index].destroy()
        del self.list_frames[index]

        for i, item in enumerate(self.list_frames[index:]):
            item.update_index(index + i)

    def on_proceed(self):
        self.drawer.clear()
        self.write_log_msg("")

        is_correct = self.get_input()

        if is_correct:
            if 3 > len(self.dots):
                self.write_log_msg(self._text_not_enough_points)
                return

            self.is_set = True
            triangle = [calc.Point(dot[0], dot[1], 0) for dot in self.triangle_dots]
            dots = [calc.Point(dot[0], dot[1], 0) for dot in self.dots]

            if calc.CALC_EPS > calc.triangle_get_square(*triangle):
                self.write_log_msg(self._text_incorrect_triangle)
                return

            circles_tangent_info = calc.triangle_find_tangent_circles(triangle, 
                                                                      dots)
            self.circle, square, self.triangle_center, \
            self.triangle_side, self.tangent_point =   \
            calc.find_biggest_square_task(triangle, dots, circles_tangent_info)
            self.selected_dots.clear()

            if None is not self.circle:
                count = 0

                for i in range(len(dots)):
                    if 0 == self.circle.get_position(dots[i]):
                        self.selected_dots.append(i)
                        count += 1

                self.write_log_msg((self._text_result
                                    .format(
                    calc.tangent_circle_count_unique(circles_tangent_info), 
                                            self.circle.center.x, 
                                            self.circle.center.y, 
                                            self.circle.radius, square, 
                                            ", ".join([str(i + 1) for i in 
                                                       self.selected_dots]), 
                                            self.tangent_point.x, 
                                            self.tangent_point.y,
                                            self.triangle_center.x,
                                            self.triangle_center.y)))

                self.draw_plot()
            else:
                self.write_log_msg(self._text_error_no_circle)

    def on_list_scroll(self, event):
        if (self.canvas_list.winfo_height()
            >= self.group_dot_list.winfo_height()):
            return

        step = 1 if 5 == event.num else -1
        self.canvas_list.yview_scroll(step, "units")


class Ui_list_item(tk.Frame):
    _path_icon_delete = "ui/outline_delete_black_24dp.png"
    _text_label = "Точка: {:d}"

    def __init__(self, parent, index, update):
        super().__init__(parent, bd=1, relief=tk.RAISED)

        self.delete_icon = (tk.PhotoImage(file=self._path_icon_delete)
                            .subsample(2, 2))
        self.label = tk.Label(self)
        self.entry_x = tk.Entry(self, justify="center")
        self.entry_y = tk.Entry(self, justify="center")
        self.button_del = tk.Button(self, image=self.delete_icon)
        self.index = index
        self.callback = update
        self.setup()

    def setup(self):
        self.update_index(self.index)
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)

        self.label.grid(row=0, column=0, sticky="wsne")
        self.entry_x.grid(row=0, column=1, sticky="wsne")
        self.entry_y.grid(row=0, column=2, sticky="wsne")
        self.button_del.grid(row=0, column=3, sticky="wsne")

        self.button_del.bind("<Button-1>", lambda event: 
                                           self.callback(self.index))

    def update_index(self, index):
        self.index = index
        self.label.configure(text=self._text_label.format(self.index + 1))

    def get_input(self):
        return [i.get().strip() for i in [self.entry_x, self.entry_y]]

