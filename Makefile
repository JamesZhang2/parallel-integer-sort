n ?= 10000000
path ?= sort/sort_serial
# usage: make n=[whatever] path=[path to ur sorting executable]
serial: build
	python3 check.py $(n) $(path)

# compiles the main program and outputs an executable
build: sort/sort_serial.cpp sort/sort_serial.hpp sort/main.cpp
	g++ -std=c++17 sort/sort_serial.cpp sort/main.cpp sort/util.cpp -o sort/sort_serial

# compiles the test program, outputs an executable, and runs it
test: sort/sort_serial.cpp sort/sort_serial.hpp sort/test_sort.cpp
	g++ -std=c++17 sort/sort_serial.cpp sort/test_sort.cpp sort/util.cpp -o sort/test_serial
	./sort/test_serial

# compiles the main program and pipes numbers.txt into the executable
sort: build
	cat numbers.txt | ./sort/sort_serial

.PHONY: clean

clean:
	rm check/check_numbers **/*.class sort/sort_serial sort/test_serial **/*.cmo **/*.cmi generate/NumberGenerator.class
