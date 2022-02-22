JAVA=java
JAVAC=javac
JFLEX=jflex
JAVACUP=java-cup-11a.jar
CLASSPATH=$(JAVACUP):.

FILE_FLEX=Labo2.flex
FILE_CUP=Labo2.cup
FILE_JAVA_NAME=Labo2
FILE_TEST_PRG_NAME=test

TEST_CLASS=test

FILE=test.txt
ifdef TESTFILE
	FILE=$(TESTFILE)
endif

all : $(FILE) sym.class parser.class $(FILE_JAVA_NAME).class $(FILE_TEST_PRG_NAME).class
	$(JAVA) -classpath $(CLASSPATH) $(TEST_CLASS) $(FILE)

$(FILE_JAVA_NAME).java : $(FILE_FLEX)
	$(JFLEX) $(FILE_FLEX)

sym.java parser.java : $(FILE_CUP)
	$(JAVA) -jar $(JAVACUP) $(FILE_CUP)

%.class : %.java
	$(JAVAC) -classpath $(CLASSPATH) $<

clean :
	rm -rf *class *~ parser.java sym.java $(FILE_JAVA_NAME).java
