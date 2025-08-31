# Compile Everything!
all:
	clang factorise.c -o factorise_clang -Wall -Werror -O3
	gcc factorise.c -o factorise_gcc -Wall -Werror -O3
	python3 -m py_compile factorise.py
	javac -g -Xlint:all -Xlint:-options factorise.java -d .
	rustc factorise.rs -C opt-level=3 -o factorise_rust

problems:
	cc create_problem.c -o create_problem
	./create_problem 4 problems.txt

# Clean Everything!
clean:
	rm factorise_* create_problem problems.txt

