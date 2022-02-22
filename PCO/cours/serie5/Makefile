CC=gcc
CFLAGS=-std=gnu11 # différent des autres makefiles
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS=-pthread
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer


ex1 : ex1.o
	@$(CC) $^ -o ex1 $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

ex1.o : ex1.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)



ex2 : thread_wrapper.o ex2.o
	@$(CC) $^ -o ex2 $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

thread_wrapper.o : thread_wrapper.h thread_wrapper.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

ex2.o : ex2.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)



clean: 
	@find . -name '*.o' -delete
	@rm -f *.o ex1 ex2 *.gch