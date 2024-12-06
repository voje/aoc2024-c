OUTDIR = bin
TARGET = $(OUTDIR)/main
# DEBUG = "-DDEBUG"

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --track-origins=yes ./$(TARGET)

build: $(TARGET)

$(TARGET): clean
	mkdir -p $(OUTDIR)
	gcc -g $(DEBUG) main.c -o $(TARGET)

clean:
	-rm /tmp/core
	-rm $(TARGET)
