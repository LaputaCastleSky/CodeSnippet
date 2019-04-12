OBJECTS=threadpool.o main.o binary_tree.o
TARGET=snippet
CC=clang
CFLAGS=-g -Wall

$(TARGET):$(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS):%o:%c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	-rm $(TARGET) $(OBJECTS)


