CC=gcc -std=c11  
CPP=g++ -std=c++17 -Wpedantic -Wshadow -lgtest -lgtest_main -lpthread
CFLAGS= -Wall -Werror -Wextra -lncurses
SANFLAG=#-fsanitize=address -g
COVFLAGS=-fprofile-arcs -ftest-coverage
OPEN = open

TEST=s21_tetris_test
TFLAGS = -lcheck -lpthread -lm

TEST_CPP=s21_snake_test

TARGET = brick_game_menu



TEST_FLAGS=-lgtest -lgtest_main

ifeq ($(CC),clang)
	TEST_FLAGS+=-lc++
endif


all: clean style_cor install style_cor

install: style_cor s21_install_console install_desktop_tetris install_desktop_snake

unistall: clean

clean:
	rm -rf *.o \
	*.a \
	s21_tetris\
	s21_snake\
	$(TEST).c \
	*.gcno  
	rm -rf *.info 
	rm -rf *.gcda
	rm -rf $(TEST)
	rm -rf $(TEST_CPP)
	rm -rf $(TEST).c
	rm -rf report
	rm -rf report_snake
	rm -rf doxygen
	rm -rf archive.tar.gz
	rm -rf doxygen
	rm -rf archive.tar.gz
	rm -rf *.out
	rm -rf s21_snake	
	rm -rf s21_tetris
	

dvi:
	doxygen
	$(OPEN) doxygen/html/index.html

dist:
	tar -czvf archive.tar.gz ./*


tests: test_snake test_tetris


s21_install_console: s21_tetris_install s21_snake_install
	$(CPP) $(CFLAGS) main.cc  -o $(TARGET)

play_console: s21_tetris_install s21_snake_install 
	$(CPP) $(CFLAGS) main.cc  -o $(TARGET)
	./$(TARGET)
	

s21_tetris_install: backend.a
	$(CC) $(CFLAGS) s21_tetris.c backend.a  -o s21_tetris -lncurses

 
s21_snake_install: backend.a
	$(CPP) $(CFLAGS) main_snake.cc backend.a  -o s21_snake -lncurses

backend.a: s21_tetris_back.o s21_snack_back.o
	ar rcs backend.a s21_tetris_back.o s21_tetris_front.o backend_snake.o frontend_snake.o 
	ranlib backend.a

s21_tetris_back.o:  
	$(CC) $(CFLAGS) -c brick_game/tetris/s21_tetris_back.c  -o s21_tetris_back.o 
	$(CC) $(CFLAGS) -c  gui/cli/tetris/s21_tetris_front.c -o s21_tetris_front.o 

s21_snack_back.o: 
	$(CPP) $(CFLAGS) -c brick_game/snake/backend_snake.cc  -o backend_snake.o 
	$(CPP) $(CFLAGS) -c  gui/cli/snake/frontend_snake.cc -o frontend_snake.o 



install_desktop_tetris:
	cd gui/desktop/tetris/tetris && \
	qmake && \
	make && \
	mv tetris.app/Contents/MacOS/tetris ../../../../desktop_tetris.out && \
	rm -rf *.o   tetris.app moc_mainwindow.cpp moc_tetriswidget.cpp .qmake.stash Makefile && \
	cd ../../../..
	

play_tetris:
	cd gui/desktop/tetris/tetris && \
	qmake && \
	make && \
	mv tetris.app/Contents/MacOS/tetris ../../../../desktop_tetris.out && \
	rm -rf *.o   tetris.app moc_mainwindow.cpp moc_tetriswidget.cpp .qmake.stash Makefile && \
	cd ../../../..
	./desktop_tetris.out


install_desktop_snake:
	cd gui/desktop/snake/snake && \
	qmake && \
	make && \
	mv snake.app/Contents/MacOS/snake ../../../../desktop_snake.out && \
	rm -rf *.o Snake.app moc_mainwindow.cpp moc_snakewidget.cpp .qmake.stash Makefile  && \
	cd ../../../..


play_snake:
	cd gui/desktop/snake/snake && \
	qmake && \
	make && \
	mv snake.app/Contents/MacOS/snake ../../../../desktop_snake.out && \
	rm -rf *.o Snake.app moc_mainwindow.cpp moc_snakewidget.cpp .qmake.stash Makefile  && \
	cd ../../../..
	./desktop_snake.out

gcov_report_tetris: clean check s21_tetris_back.a
	$(CC) --coverage -o $(TEST) -lcurses $(TEST).c  brick_game/tetris/s21_tetris_back.c s21_tetris_back.a $(TFLAGS)   
	./$(TEST) 
	lcov -t "$(TEST)" -o $(TEST).info -c -d . --rc branch_coverage=1
	genhtml -o report $(TEST).info --rc branch_coverage=1
	open ./report/index.html


test_tetris: clean s21_tetris_back.a check
	$(CC) -o $(TEST) $(TEST).c  -lcurses s21_tetris_back.a $(TFLAGS) 
	./$(TEST)

s21_tetris_back.a:  
	$(CC) $(CFLAGS) -c brick_game/tetris/s21_tetris_back.c  -o s21_tetris_back.o 
	$(CC) $(CFLAGS) -c  gui/cli/tetris/s21_tetris_front.c -o s21_tetris_front.o 
	ar rcs s21_tetris_back.a s21_tetris_back.o s21_tetris_front.o 
	ranlib s21_tetris_back.a


check:
	checkmk clean_mode=1 $(TEST).check > $(TEST).c    
	clang-format -i -style=Google *.c 

style:
	clang-format -n -style=Google  brick_game/tetris/*.c  brick_game/tetris/*.h gui/cli/tetris/*.c gui/cli/tetris/*.h
	clang-format -n -style=Google  brick_game/snake/*.cc brick_game/snake/*.h gui/cli/snake/*.cc gui/cli/snake/*.h
	clang-format -n -style=Google   gui/desktop/snake/snake/*.cpp  gui/desktop/snake/snake/*.h
	clang-format -n -style=Google   gui/desktop/tetris/tetris/*.cpp  gui/desktop/tetris/tetris/*.h
	clang-format -n -style=Google   *.cc *.c *.h

style_cor:
	clang-format -i -style=Google  brick_game/tetris/*.c  brick_game/tetris/*.h gui/cli/tetris/*.c gui/cli/tetris/*.h
	clang-format -i -style=Google  brick_game/snake/*.cc brick_game/snake/*.h gui/cli/snake/*.cc gui/cli/snake/*.h
	clang-format -i -style=Google   gui/desktop/snake/snake/*.cpp  gui/desktop/snake/snake/*.h
	clang-format -i -style=Google   gui/desktop/tetris/tetris/*.cpp  gui/desktop/tetris/tetris/*.h
	clang-format -i -style=Google   *.cc *.c *.h


test_snake: backend_snake.a
	$(CPP) $(CFLAGS) -o $(TEST_CPP) $(TEST_CPP).cpp  backend_snake.a $(TFLAGS) 
	./$(TEST_CPP)


backend_snake.a: 
	$(CPP) $(CFLAGS) -c brick_game/snake/backend_snake.cc -o backend_snake.o
	ar rcs backend_snake.a backend_snake.o
	ranlib backend_snake.a


gcov_report_snake: clean backend_snake.a
	$(CPP) --coverage -o $(TEST_CPP) -lcurses $(TEST_CPP).cpp  brick_game/snake/backend_snake.cc backend_snake.a $(TFLAGS)   
	./$(TEST_CPP)
	lcov -t "$(TEST_CPP)" -o $(TEST_CPP).info -c -d . --rc branch_coverage=1 --ignore-errors inconsistent --ignore-errors empty
	lcov --extract $(TEST_CPP).info '*brick_game/snake/backend_snake.cc' -o $(TEST_CPP)_filtered.info
	genhtml -o report_snake $(TEST_CPP)_filtered.info --rc branch_coverage=1
	open ./report_snake/index.html



