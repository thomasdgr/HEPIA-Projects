all: clean build
lib: hepia_gpu_lib.o
build: hepia_gpu_lib.o
	nvcc main.cu hepia_gpu_lib.o -o laplace_gpu.out 
test: clean hepia_gpu_lib.o
	nvcc test_0.cu hepia_gpu_lib.o -o test_gpu.out
hepia_gpu_lib.o:
	nvcc -c laplace_solver.cu -o hepia_gpu_lib.o
clean:
	rm -f hepia_gpu_lib.o laplace_gpu.out test_gpu.out
