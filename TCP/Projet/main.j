.class public nombreSecret
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit stack 20000
.limit locals 200
.var 0 is min I
.var 1 is max I
.var 2 is crt I
.var 3 is consigne I
.var 4 is trouve Z
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "Bonjour, je vais devoir deviner le nombre auquel vous pensez"
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "\nEntre 0 et quelle valeur souhaitez vous jouer ? : "
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
new java/util/Scanner
dup
getstatic java/lang/System/in Ljava/io/InputStream;
invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
invokevirtual java/util/Scanner/nextInt()I
istore 1
label_5:
iload 1
ldc 0
if_icmple label_6
ldc 0
goto label_7
label_6:
ldc 1
label_7:
ifeq label_8
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "\nEntre 0 et quelle valeur souhaitez vous jouer ? :"
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
new java/util/Scanner
dup
getstatic java/lang/System/in Ljava/io/InputStream;
invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
invokevirtual java/util/Scanner/nextInt()I
istore 1
goto label_5
label_8:
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "\n-> Si votre nombre est plus grand que celui que je propose, entrez 1"
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "\n-> Si votre nombre est plus petit que celui que je propose, entrez -1"
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "\n-> Si votre nombre est le même que celui que je propose, entrez 0\n\n"
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
ldc 0
istore 0
iload 1
iload 0
isub
ldc 2
idiv
istore 2
ldc 2
istore 3
ldc 0
istore 4
label_9:
iload 4
ldc 0
if_icmpeq label_10
ldc 0
goto label_11
label_10:
ldc 1
label_11:
ifeq label_12
label_13:
iload 3
ldc 1
if_icmpne label_14
ldc 0
goto label_15
label_14:
ldc 1
label_15:
iload 3
ldc 1
ineg
if_icmpne label_16
ldc 0
goto label_17
label_16:
ldc 1
label_17:
iload 3
ldc 0
if_icmpne label_18
ldc 0
goto label_19
label_18:
ldc 1
label_19:
iand
iand
ifeq label_20
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "Votre nombre est-il plus grand, plus petit ou égal à "
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
iload 2
getstatic java/lang/System/out Ljava/io/PrintStream;
swap
invokevirtual java/io/PrintStream/print(I)V
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc " ? : "
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
new java/util/Scanner
dup
getstatic java/lang/System/in Ljava/io/InputStream;
invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
invokevirtual java/util/Scanner/nextInt()I
istore 3
goto label_13
label_20:
iload 3
ldc 0
if_icmpeq label_21
ldc 0
goto label_22
label_21:
ldc 1
label_22:
ifeq label_23
ldc 1
istore 4
goto label_24
label_23:
iload 3
ldc 1
ineg
if_icmpeq label_25
ldc 0
goto label_26
label_25:
ldc 1
label_26:
ifeq label_27
iload 2
istore 1
goto label_28
label_27:
iload 2
istore 0
label_28:
iload 1
iload 0
iadd
ldc 2
idiv
istore 2
label_24:
ldc 2
istore 3
goto label_9
label_12:
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "je gagne toujours à ce jeu ! votre nombre était : "
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
iload 2
getstatic java/lang/System/out Ljava/io/PrintStream;
swap
invokevirtual java/io/PrintStream/print(I)V
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "\n"
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
return
.end method
