# DEBUG = "-DDEBUG"

# .so files need to be named lib<something> in order to be
# picked up by $ld
TARGETS=lib/libklist.so lib/libkgraph.so

build: clean dirs $(TARGETS)

test: test-klist test-kgraph

clean:
	-rm -r lib build

dirs:
	mkdir -p lib build

# klist
build/klist.o:
	gcc -c -fPIC src/klist.c -Iinclude -o build/klist.o

lib/libklist.so: build/klist.o
	gcc -shared build/klist.o -o lib/libklist.so

test-klist:
	gcc -Iinclude src/klist_test.c src/klist.c -o build/klist_test
	valgrind ./build/klist_test

# kgraph
build/kgraph.o:
	gcc -c -fPIC src/kgraph.c -Iinclude -o build/kgraph.o

lib/libkgraph.so: build/kgraph.o
	gcc -shared build/kgraph.o -o lib/libkgraph.so

test-kgraph:
	gcc -Iinclude src/kgraph_test.c src/kgraph.c -o build/kgraph_test
	valgrind ./build/kgraph_test
