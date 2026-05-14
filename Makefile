GXX=g++

all: search
	./search
	$(MAKE) plot

search: flat.o tree.o search.o hash.o rb_tree.o
	$(GXX) $^ -o $@

flat.o: flat.cpp flat.hpp
	$(GXX) $< -c -o $@

tree.o: tree.cpp tree.hpp flat.hpp
	$(GXX) -c $< -o $@

hash.o: hash.cpp hash.hpp flat.hpp
	$(GXX) -c $< -o $@

rb_tree.o: rb_tree.cpp rb_tree.hpp flat.hpp
	$(GXX) -c $< -o $@

search.o: search.cpp flat.hpp tree.hpp
	$(GXX) -c $< -o $@

clean:
	rm -f CSV/*.csv
	rm -f *.o search
	echo "" > docs/collisions.txt
	echo "" > docs/times_with_fill.txt
	echo "" > docs/times_no_fill.txt
	rm -f docs/plot.png
	rm -rf docs/html docs/latex
	clear

gen:
	mkdir -p CSV
	python3 gen.py 100
	python3 gen.py 2500
	python3 gen.py 7000
	python3 gen.py 10000
	python3 gen.py 50000
	python3 gen.py 100000
	python3 gen.py 250000
	python3 gen.py 500000
	python3 gen.py 750000
	python3 gen.py 1000000

clang:
	touch .clang-format
	echo "---" > .clang-format
	echo "BasedOnStyle: Google" >> .clang-format
	clang-format -i *.cpp *.hpp
	rm -f .clang-format
	clear

plot:
	python3 plot.py

dox:
	doxygen ./doxygen_config
	open docs/html/index.html

rebuild: clean all

.PHONY = all search clean clang rebuild gen dox plot