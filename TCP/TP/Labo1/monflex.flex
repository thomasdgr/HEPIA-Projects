import java_cup.runtime.*;
import java.util.Vector;

%%
%class Lexer
%line
%column
%cup

%{

public void yyerror() { System.out.println("error line "+yyline+" column "+yycolumn+" " +yytext()); }

%}

nb = [0-9]+
str = [A-Za-z]+

%%

"/"    { return new Symbol(sym.SLASH); }
">"    { return new Symbol(sym.CLOSE); }
"="    { return new Symbol(sym.EQUAL); }
"<"    { return new Symbol(sym.OPEN); }
","    { return new Symbol(sym.COMA); }
"\""   { return new Symbol(sym.TICK); }
{nb}   { return new Symbol(sym.NB, new Integer(yytext())); }
{str} { return new Symbol(sym.STR, yytext()); }

/* -------------------------------------------------
	Caracteres non pris en compte
   ------------------------------------------------- */

(\ |\t|\n|\r|\r\n) {;}
. {;}