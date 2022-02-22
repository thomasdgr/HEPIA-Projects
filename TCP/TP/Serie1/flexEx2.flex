%%
/* options */
%class content
%unicode
%line
%column
%standalone

%{
    String mot = "";
    public static boolean isPalindrome(String mot){
        int index1 = 0;
        int index2 = mot.length()-1;
        while(index2 > index1){
           if(mot.charAt(index1) != mot.charAt(index2)){
                System.out.println(mot + " n'est pas un palindrome");
               return false;
           }
           index1++;
           index2--;
        }
        System.out.println(mot + " est un palindrome");
        return true;
    }
%}

%{eof
    isPalindrome(mot);
%eof}

/* models */

word = [a-zA-Z0-9]+
separator = " "|";"|"." 

%%
/* rules */
{separator} {isPalindrome(mot);}
{word} {mot = yytext();}
[\n] {isPalindrome(mot);}
. {}