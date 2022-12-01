
DIR_SRC    := src
DIR_HEADER := inc
DIR_OUT    := out
DIR_SHARED := shared
DIR_UI     := ui

SRCS = $(wildcard $(DIR_SRC)/*.cpp)
OBJS = $(SRCS:$(DIR_SRC)/%.cpp=$(DIR_OUT)/%.o)
DEPS = $(wildcard $(DIR_OUT)/*.d)
UIS  = $(wildcard $(DIR_UI)/*.ui)

FLAGS = -std=c++11 -Wall -Werror -Wpedantic -Wextra -I$(DIR_HEADER) -I$(DIR_OUT)
LFLAGS = $(shell pkg-config --libs Qt5Widgets)
ADDFLAGS =

MOCFLAGS = -I$(DIR_OUT) -I$(DIR_HEADER)

.PHONY: build debug clean run test

run: build
run:
	./app.exe

drun: debug
drun:
	./app.exe

$(DIR_OUT)/.builddebug: | $(DIR_OUT)
	rm -f $(DIR_OUT)/.build*
	rm -f $(DIR_OUT)/*.o
	touch $(DIR_OUT)/.builddebug

$(DIR_OUT)/.buildrelease: | $(DIR_OUT)
	rm -f $(DIR_OUT)/.build*
	rm -f $(DIR_OUT)/*.o
	touch $(DIR_OUT)/.buildrelease

build: $(DIR_OUT)/.buildrelease app.exe

debug: FLAGS += -g3
debug: $(DIR_OUT)/.builddebug app.exe

$(DIR_OUT):
	mkdir -p $(DIR_OUT)

$(DIR_OUT)/%.o: ADDFLAGS = 
$(DIR_OUT)/mainwindow.o: ADDFLAGS = $(shell pkg-config --cflags Qt5Widgets)
$(DIR_OUT)/main.o: ADDFLAGS = $(shell pkg-config --cflags Qt5Widgets)
$(DIR_OUT)/qcanvas.o: ADDFLAGS = $(shell pkg-config --cflags Qt5Widgets)

$(DIR_OUT)/%.o: $(DIR_SRC)/%.cpp | $(DIR_OUT)
	@g++ $(FLAGS) $(ADDFLAGS) -MM -MF $(@:%.o=%.d) -MT $@ -c -o /dev/null \
		 $(@:$(DIR_OUT)/%.o=$(DIR_SRC)/%.cpp)
	g++ $(FLAGS) $(ADDFLAGS) -c -o $@ $(@:$(DIR_OUT)/%.o=$(DIR_SRC)/%.cpp)

$(DIR_OUT)/%.h: $(DIR_UI)/%.ui | $(DIR_OUT)
	uic -o $@ $<

$(DIR_OUT)/moc_%.cpp: $(DIR_HEADER)/%.h | $(DIR_OUT)
	moc $(MOCFLAGS) -o $@ $<

app.exe: $(OBJS) | $(DIR_OUT)
	g++ $(FLAGS) -o app.exe $(OBJS) $(LFLAGS)

include $(DEPS)
$(DIR_OUT)/main.o: $(UIS:$(DIR_UI)/%.ui=$(DIR_OUT)/%.h)
$(DIR_OUT)/mainwindow.o: $(UIS:$(DIR_UI)/%.ui=$(DIR_OUT)/%.h)
$(DIR_OUT)/mainwindow.o: $(DIR_OUT)/moc_mainwindow.cpp
$(DIR_OUT)/qcanvas.o: $(DIR_OUT)/moc_qcanvas.cpp

clean:
	rm -f .build*
	rm -f $(DIR_OUT)/*

