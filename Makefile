LIB_DIR=./lib
a.out: index.o map.o image_io.o
	$(CC) $(LIB_DIR)/*.c $^ 

map.o: map.h
image_io.o: image_io.h libbmp.o gifenc.o
