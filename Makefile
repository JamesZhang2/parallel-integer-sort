n ?= 10000000
path ?= sort/sort
# usage: make n=[whatever] path=[path to ur sorting executable]
python: build
	python3 check.py $(n) $(path)

python_test: build
	python3 test.py $(n) $(path)

# compiles the main program and outputs an executable
build: sort/sort.cpp sort/sort.hpp sort/main.cpp
	g++ -std=c++17 sort/sort.cpp sort/main.cpp sort/util.cpp -o sort/sort

# compiles the test program, outputs an executable, and runs it
test: sort/sort.cpp sort/sort.hpp sort/test_sort.cpp
	g++ -std=c++17 sort/sort.cpp sort/test_sort.cpp sort/util.cpp -o sort/test
	./sort/test

# compiles the main program and pipes numbers.txt into the executable
sort: build
	cat numbers.txt | ./sort/sort $(method)

.PHONY: clean

clean:
	rm check/check_numbers **/*.class sort/sort sort/test **/*.cmo **/*.cmi generate/NumberGenerator.class
