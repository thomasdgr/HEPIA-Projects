
import java_cup.runtime.*;
import java.util.*;

%%
%class Lexer
%line
%column
%cup

%{

// Print parsing errors
public void yyerror() {
       System.out.println("error line " +yyline + " column " +yycolumn + " " +yytext());
}

%}

/* models */
ident = [a-zA-Z][A-Za-z0-9]*
constantInt = [0-9]+
constanteStr = \"([^\"]|\"\")*\" // double " to add in string
comma = ,
semicolon = ;
equal = "="
openparent = "("
closeparent = ")"
tilda = "~"

// ignored
comment = \/\/.*
blank = [\s|\t|\n|\r]+

%%
/* rules */

programme       { return new Symbol(sym.PRG, yyline, yycolumn); }
debutprg        { return new Symbol(sym.STARTPRG, yyline, yycolumn); }
finprg          { return new Symbol(sym.ENDPRG, yyline, yycolumn); }
constante       { return new Symbol(sym.CONSTANT, yyline, yycolumn); }
{semicolon}     { return new Symbol(sym.SEMICOLON, yyline, yycolumn); }
//debutfonc     { return new Symbol(sym.STARTFUNC, yyline, yycolumn); }
//finfonc       { return new Symbol(sym.ENDFUNC, yyline, yycolumn); }
{openparent}    { return new Symbol(sym.OPENPARENT, yyline, yycolumn); }
{closeparent}   { return new Symbol(sym.CLOSEPARENT, yyline, yycolumn); }
{comma}         { return new Symbol(sym.COMMA, yyline, yycolumn); }
{equal}         { return new Symbol(sym.EQUAL, yyline, yycolumn); }
//{doublepoints}{ return new Symbol(sym.DOUBLEPOINTS, yyline, yycolumn); } doublepoints = ".."
//{openbrack}   { return new Symbol(sym.OPENBRACK, yyline, yycolumn); } openbrack = "["
//{closebrack}  { return new Symbol(sym.CLOSEBRACK, yyline, yycolumn); } closebrack = "]"

{constantInt}   { return new Symbol(sym.INTEGERCONST, yyline, yycolumn, Integer.parseInt(yytext())); }
{constanteStr}  { return new Symbol(sym.STRINGCONST, yyline, yycolumn, yytext()); }

entier          { return new Symbol(sym.TINTEGER, yyline, yycolumn); }
booleen         { return new Symbol(sym.TBOOLEAN, yyline, yycolumn); }
lire            { return new Symbol(sym.READ, yyline, yycolumn); }
ecrire          { return new Symbol(sym.WRITE, yyline, yycolumn); }
//retourne      { return new Symbol(sym.RETURN, yyline, yycolumn); }
si              { return new Symbol(sym.IF, yyline, yycolumn); }
alors           { return new Symbol(sym.THEN, yyline, yycolumn); }
sinon           { return new Symbol(sym.ELSE, yyline, yycolumn); }
finsi           { return new Symbol(sym.ENDIF, yyline, yycolumn); }
tantque         { return new Symbol(sym.WHILE, yyline, yycolumn); }
faire           { return new Symbol(sym.DO, yyline, yycolumn); }
fintantque      { return new Symbol(sym.ENDWHILE, yyline, yycolumn); }
pour            { return new Symbol(sym.FOR, yyline, yycolumn); }
allantde        { return new Symbol(sym.FROM, yyline, yycolumn); }
a               { return new Symbol(sym.TO, yyline, yycolumn); }
finpour         { return new Symbol(sym.ENDFOR, yyline, yycolumn); }
vrai            { return new Symbol(sym.TRUE, yyline, yycolumn); }
faux            { return new Symbol(sym.FALSE, yyline, yycolumn); }


\+              { return new Symbol(sym.PLUS, yyline, yycolumn); }
-               { return new Symbol(sym.MINUS, yyline, yycolumn); }
\*              { return new Symbol(sym.TIMES, yyline, yycolumn); }
\/              { return new Symbol(sym.DIVIDE, yyline, yycolumn); }
==              { return new Symbol(sym.EQUALS, yyline, yycolumn); }
"<>"            { return new Symbol(sym.DIFF, yyline, yycolumn); }
"<"             { return new Symbol(sym.INF, yyline, yycolumn); }
"<="            { return new Symbol(sym.INFEQUAL, yyline, yycolumn); }
>               { return new Symbol(sym.SUP, yyline, yycolumn); }
>=              { return new Symbol(sym.SUPEQUAL, yyline, yycolumn); }
et              { return new Symbol(sym.AND, yyline, yycolumn); }
ou              { return new Symbol(sym.OR, yyline, yycolumn); }

{tilda}         { return new Symbol(sym.TILDA, yyline, yycolumn); }
non             { return new Symbol(sym.NOT, yyline, yycolumn); }

{ident}         { return new Symbol(sym.IDENT, yyline, yycolumn, yytext()); }

// ignored tags
{comment}       {;}
{blank}         {;}
