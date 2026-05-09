GXX=g++

all: search
	./search

search: flat.o tree.o search.o
	$(GXX) $^ -o $@

flat.o: flat.cpp flat.hpp
	$(GXX) $< -c -o $@

tree.o: tree.cpp tree.hpp flat.hpp
	$(GXX) -c $< -o $@

search.o: search.cpp flat.hpp tree.hpp
	$(GXX) -c $< -o $@

clean:
	rm -f CSV/*.csv
	rm -f *.o search
	clear

gen:
	mkdir -p CSV
	python3 gen.py 100
	python3 gen.py 600
	python3 gen.py 1000
	python3 gen.py 2500
	python3 gen.py 7000
	python3 gen.py 10000
	python3 gen.py 30000
	python3 gen.py 50000
	python3 gen.py 100000
	python3 gen.py 200000

clang:
	touch .clang-format
	echo "---" > .clang-format
	echo "BasedOnStyle: Google" >> .clang-format
	clang-format -i *.cpp *.hpp
	rm -f .clang-format
	clear

rebuild: clean search

.PHONY = all search clean clang rebuild gen