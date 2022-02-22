include ../../common.mk

O_DEPS+= test.o test_filter_functions.o test_map_functions.o test_point_3d.o test_lidar.o test_stl.o test_triangle.o test_vector.o test_triangulation_lst.o test_triangulation.o test_lst_vector.o

LDFLAGS+= -lcunit

.PHONY: all
all: test
	@./test

test: test.o
	@$(CC) $(CFLAGS) $(CFLAGS_ASAN) $(O_DEPS) $(LDFLAGS) $(LDFLAGS_ASAN) -o $@ 

test.o: test.c test_filter_functions.o test_map_functions.o test_point_3d.o test_lidar.o test_stl.o test_triangle.o test_vector.o test_triangulation.o test_triangulation_lst.o test_lst_vector.o
	@$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_filter_functions.o: test_filter_functions.c test_filter_functions.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_map_functions.o: test_map_functions.c test_map_functions.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_point_3d.o: test_point_3d.c test_point_3d.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_lidar.o: test_lidar.c test_lidar.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_stl.o: test_stl.c test_stl.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_triangle.o: test_triangle.c test_triangle.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_triangulation.o: test_triangulation.c test_triangulation.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_triangulation_lst.o: test_triangulation_lst.c test_triangulation_lst.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_vector.o: test_vector.c test_vector.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test_lst_vector.o: test_lst_vector.c test_lst_vector.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean:
	@rm -f *.o test
