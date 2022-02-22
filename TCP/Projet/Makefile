all : clean input.txt sym.class parser.class Lexer.class Main.class
	@java -classpath java-cup-11a.jar:./src:. Main input.txt
	@java -jar jasmin.jar main.j

Lexer.java : monflex.flex
	@jflex monflex.flex

sym.java parser.java : moncup.cup
	@java -jar java-cup-11a.jar moncup.cup

%.class : %.java
	@javac -classpath java-cup-11a.jar:.:./src:. $<

clean :
	@rm -rf *.class *~ parser.java sym.java Lexer.java HepiaLexer.java src/*.class