all: ex1 ex2 ex3

ex1:
	@jflex flexEx1.flex
	@javac content.java
	@java content input.txt > ex1.txt

ex2:
	@jflex flexEx2.flex
	@javac content.java
	@java content input.txt > ex2.txt
	
ex3:
	@jflex flexEx3.flex
	@javac content.java
	@java content input.txt > ex3.txt

clean:
	rm content.class content.java ex*.txt