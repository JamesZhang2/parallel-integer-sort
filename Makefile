n ?= 100000
path ?= sort/sort_numbers
# usage: make n=[whatever] path=[path to ur sorting executable]
serial: sort/sort_numbers
	python3 check.py $(n) $(path)

build: sort/sort_numbers.cpp
	g++ sort/sort_numbers.cpp -o sort_serial -std=c++17

test: sort/sort_numbers.cpp
	g++ sort/sort_numbers.cpp -o sort_serial -std=c++17
	./sort_serial

sort: sort/sort_numbers.cpp
	g++ sort/sort_numbers.cpp -o sort_serial -std=c++17
	cat numbers.txt | ./sort_serial

.PHONY: clean

clean:
	rm check/check_numbers **/*.class sort/sort_numbers **/*.cmo **/*.cmi generate/NumberGenerator.class
