CC = gcc
CFLAGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic

build: parent child

parent: main.cc parent.cc
	$(CC) $(CFLAGS) -o parent $^

child: child.cc
	$(CC) $(CFLAGS) -o child $^
	
.PHONY: clean

clean:
	rm parent child