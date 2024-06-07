TEST_FLAGS= -lgtest_main -pthread -lgtest
GCC= g++ -Wall -Wextra -Werror -std=c++17

install: clean
	mkdir ../build
	cp -rf img ../build
	cd ../build && cmake ../ && make

uninstall:
	rm -rf ../build

desktop: install
	cd ../build && ./desktopBrickGame

cli: install
	cd ../build && ./consoleBrickGame

test:
	clear
	$(GCC) $(TEST_FLAGS) -g -o test tests/snakeTest.cpp brick_game/snake/SnakeModel.cpp
	./test

dist: install
	mkdir -p BrickGames
	mkdir -p BrickGames/src
	touch BrickGames/Makefile
	echo -e ".PHONY: all dvi \n \
		all: dvi run_desktop\n \
		run_cli:\n\t \
		cd build && ./consoleBrickGame\n\n \
		run_desktop:\n\t \
		cd build && ./desktopBrickGame\n \
		dvi:\n\txdg-open ../dvi/index.html" >> BrickGames/Makefile
	cp -R ../build ../dvi img BrickGames/
	mv BrickGames/img BrickGames/src
	tar cvzf BrickGames.tgz BrickGames/
	mv BrickGames.tgz ../
	rm -rf BrickGames/


clean:
	rm -rf ../build
	rm -rf test
	rm -rf SnakeScore.txt
	rm -rf ../BrickGames
	rm -rf ../*.tgz
	clear

dvi:
	xdg-open ../dvi/index.html




