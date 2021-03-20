LIB_DIR=./lib
AUTOMATA_DIR=./automata

a.out: index.o map.o image_io.o \
$(AUTOMATA_DIR)/gol.o $(AUTOMATA_DIR)/gol_torus.o \
$(LIB_DIR)/gifenc.o $(LIB_DIR)/libbmp.o
	$(CC) $^ 

map.o: map.h
$(AUTOMATA_DIR)/gol_torus.o: automata/gol_torus.h
$(AUTOMATA_DIR)/gol.o: automata/gol.h
$(LIB_DIR)/gifenc.o: $(LIB_DIR)/gifenc.h
$(LIB_DIR)/libbmp.o: $(LIB_DIR)/libbmp.h
image_io.o: image_io.h 

clean:
	@-rm -f *.o