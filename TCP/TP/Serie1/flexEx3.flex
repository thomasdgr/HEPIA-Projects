%%
/* options */
%class content
%unicode
%line
%column
%standalone

%{
    int nbParenthesesOuvertes = 0;
    boolean fermee = true;
%}

%{eof
    if (fermee && (nbParenthesesOuvertes == 0))
        System.out.println("L'expression est bien parenthésée");
    else
        System.out.println("L'expression n'est pas bien parenthésée");
%eof}

/* models */

parentheseGauche =\(
parentheseDroite =\)

%%
/* rules */

{parentheseGauche} {nbParenthesesOuvertes++;}
{parentheseDroite} {nbParenthesesOuvertes--; fermee = (nbParenthesesOuvertes == 0);}
[\n] {}
. {}