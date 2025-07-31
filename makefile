# Compile Everything!
all:
	clang factorise.c -o factorise_clang -Wall -Werror -O3
	gcc factorise.c -o factorise_gcc -Wall -Werror -O3
	python3 -m py_compile factorise.py
	javac -g -Xlint:all -Xlint:-options factorise.java -d .
	rustc factorise.rs -C opt-level=3 -o factorise_rust

# Clean Everything!
clean:
	rm factorise_*

