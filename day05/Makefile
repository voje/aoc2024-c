OUTDIR = bin
TARGET = $(OUTDIR)/main
# DEBUG = "-DDEBUG"
LIBPATH=/home/kristjan/git/aoc2024-c/global/lib

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --track-origins=yes ./$(TARGET)

build: $(TARGET)

$(TARGET): clean
	mkdir -p $(OUTDIR)

	# This works
	gcc -g $(DEBUG) main.c -I../global/include -L../global/lib -lklist -o $(TARGET)

clean:
	# -rm /tmp/core
	-rm $(TARGET)
