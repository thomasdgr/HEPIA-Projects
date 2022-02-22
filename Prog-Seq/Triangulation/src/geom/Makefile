include ../../common.mk

all: point_3d.o triangle.o triangulation.o triangulation_lst.o

point_3d.o: point_3d.c point_3d.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

triangle.o: triangle.c triangle.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

triangulation.o: triangulation.c triangulation.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

triangulation_lst.o: triangulation_lst.c triangulation_lst.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean: 
	@rm -f *.o
