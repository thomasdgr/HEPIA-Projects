/* Michaël Minelli
 * Technique de compilation
 * ITI Jour 2ème
 * Labo 3 : Analyseur SGML
 */
import java_cup.runtime.*;
import java.util.Vector;
%%
%class Labo3
%line
%column
%cup
%{
%}

LETTRE=[A-Z]
LETTRE_MIN=[a-z]
ALPHABET=({LETTRE_MIN}|{LETTRE})

FERMANTE=\<\/{LETTRE}\>
DEBUT=\<{LETTRE}
ID={LETTRE_MIN}\=\".*\"
FIN_AUTOFERMANTE=\/\>
FIN=\>
IGNORE=(\ |\t|\n|{ID})

VAR=\<#set\ {ALPHABET}+\=\".*\"\/\>
IF=\<#if\ {ALPHABET}+\=\=\".*\"\>
FI=\<\#if\/\>

%%

{FERMANTE} {return new Symbol(sym.FERMANTE, String.valueOf(yytext().toCharArray()[2]));}
{DEBUT}   {return new Symbol(sym.DEBUT, String.valueOf(yytext().toCharArray()[1]));}
{FIN_AUTOFERMANTE} {return new Symbol(sym.FIN_AUTOFERMANTE);}
{FIN} {return new Symbol(sym.FIN);}

{VAR} {return new Symbol(sym.VAR, yytext());}
{IF} {return new Symbol(sym.IF, yytext());}
{FI} {return new Symbol(sym.FI);}

{IGNORE} {;}
. {return new Symbol(sym.TEXT_OR_ERROR, yytext());}
