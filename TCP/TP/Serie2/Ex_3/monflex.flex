
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

/* models */

id = [0-9]+

%%
/* rules */

"+"   { return new Symbol(sym.ADD); }
"-"   { return new Symbol(sym.SUB); }
"/"   { return new Symbol(sym.DIV); }
"*"   { return new Symbol(sym.MUL); }
"("   { return new Symbol(sym.PG); }
")"   { return new Symbol(sym.PD) ; }
";"   { return new Symbol(sym.VRG); }
{id}   { return new Symbol(sym.ID, new Integer(yytext())); }

/* -------------------------------------------------
	Caracteres non pris en compte
   ------------------------------------------------- */

[\ |\t|\n|\r|\r\n] {}