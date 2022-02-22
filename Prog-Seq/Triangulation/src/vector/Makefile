include ../../common.mk

all: vector.o filter_functions.o map_functions.o vector_2d.o vector_3d.o vector_i_edge.o vector_i_triangle.o vector_list.o vector_list_2d.o vector_list_3d.o vector_list_i_edge.o vector_list_i_triangle.o

vector.o: vector/vector.c vector/vector.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

filter_functions.o: filter_functions.c filter_functions.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

map_functions.o: map_functions.c map_functions.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

vector_2d.o: vector/vector_2d.c vector/vector_2d.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

vector_3d.o: vector/vector_3d.c vector/vector_3d.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

vector_i_edge.o: vector/vector_i_edge.c vector/vector_i_edge.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

vector_i_triangle.o: vector/vector_i_triangle.c vector/vector_i_triangle.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

vector_list.o: vector_list/vector_list.c vector_list/vector_list.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

vector_list_2d.o: vector_list/vector_list_2d.c vector_list/vector_list_2d.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

vector_list_3d.o: vector_list/vector_list_3d.c vector_list/vector_list_3d.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

vector_list_i_edge.o: vector_list/vector_list_i_edge.c vector_list/vector_list_i_edge.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

vector_list_i_triangle.o: vector_list/vector_list_i_triangle.c vector_list/vector_list_i_triangle.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean:
	@rm -f *.o
