a.out: index.o map.o
	$(CC) $^

map.o: map.h