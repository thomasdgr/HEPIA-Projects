
import java_cup.runtime.*;
import java.util.Vector;

%%
%class Lexer
%line
%column
%cup

%{

public void yyerror() {
      System.out.println("error line "+yyline+" column "+yycolumn+" " +yytext());
}

%}

%%

"a"   { return new Symbol(sym.CHAR_A); }
"b"   { return new Symbol(sym.CHAR_B); }
"c"   { return new Symbol(sym.CHAR_C); }
"d"   { return new Symbol(sym.CHAR_D); }


/* -------------------------------------------------
	Caracteres non pris en compte
   ------------------------------------------------- */

[\ |\t|\n|\r|\r\n]                  {}


// stock tous les symboles dans un buffer avant d'envoyer a cup