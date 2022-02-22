CC=gcc
CFLAGS=-std=gnu11 -g -O3 -Wall -Wextra -pedantic
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=address
CFLAGS_ASAN+=-fsanitize=undefined -fsanitize=leak
# CFLAGS=-std=gnu11 -g -Wall -Wextra -pedantic
# CFLAGS_ASAN=-fno-omit-frame-pointer
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer
# LDFLAGS_ASAN=-fno-omit-frame-pointer
