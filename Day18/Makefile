# the compiler
COMPILER=g++

 # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

main: main.cpp libshape.so
	@echo -- Building main using shared library shape from $^
	@echo -- run "export LD_LIBRARY_PATH=."
	$(COMPILER) main.cpp -L . -l shape -o main

main-debug: main.cpp libshape.so
	@echo -- Building main using shared library shape from $^
	@echo -- run "export LD_LIBRARY_PATH=."
	$(COMPILER) $(CFLAGS) main.cpp libshape.so -o main-debug

libshape.so: ../Day13/shape.cpp
	@echo -- Building shared library $@
	$(COMPILER) --shared -fPIC ../Day13/shape.cpp -o libshape.so

clean:
	@echo -- Cleaning up folder
	rm -r libshape.so main