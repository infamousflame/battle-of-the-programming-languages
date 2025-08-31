# Battle of the Programming Languages

I am using this repo to benchmark popular programming language compilers to
see which one is the fastest.

The problem they all have to solve is factoring a 64-bit integer into primes.

You can run this yourself if you want, you'll need Make and the following
compilers:
* GCC
* Clang
* CPython
* PyPy
* Javac (from any JDK should do)
* Rustc

Use `make problems` to create a file with four integers to factor. Then `make`
to compile all the programs. If you don't have / want to use some of the
compilers, you could inspect the makefile to remove some.


