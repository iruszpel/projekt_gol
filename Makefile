a.out: index.o map.o image_io.o
	$(CC) $^ libbmp.c

map.o: map.h
libbmp.o: libbmp.h
image_io.o: image_io.h libbmp.o
