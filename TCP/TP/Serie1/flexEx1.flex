%%
/* options */
%class content
%unicode
%line
%column
%standalone

%{
    int nbMots = 0;
    int nbLignes = 1;
    int nbChar = 0;
%}

%{eof
      System.out.println( "texte composé de " + nbLignes + " ligne(s) "
      + nbMots + " mot(s) " + nbChar + " Caractère(s)");
%eof}

/* models */

char =[a-zA-Z0-9]
word =[ ]+

%%
/* rules */

{char} {nbChar++;}
{word} {nbMots++; nbChar++;}
[\n]   {nbMots++; nbLignes++;}
. {}