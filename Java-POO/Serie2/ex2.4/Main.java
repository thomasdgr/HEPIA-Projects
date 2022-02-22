import java.lang.Math;

public class Main{

    public static void printFir(int n){
        String display = "";
        int millieuGauche = n-1;
        int millieuDroite = n-1;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < (n*2)-1; j++){
                if(j < millieuGauche || j > millieuDroite){
                    display = display + " ";
                } else {
                    display = display + "*";
                }
            }
            System.out.println(display);
            millieuDroite++;
            millieuGauche--;
            display = "";
        }
    }

    public static void main(String[] args){
        printFir(8);
    }
}