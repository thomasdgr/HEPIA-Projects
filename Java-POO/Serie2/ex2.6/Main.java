import java.lang.Math;

public class Main{

    public static double approximatePi(int n){
        double res = 0;
        for(int i = 1; i <= n; i++ ){
            res = res + (1/Math.pow(n,4));
        }
        return Math.sqrt(Math.sqrt(res * 90));
    }

    public static void main(String[] args){
        int n = 8;
        System.out.println("NE MARCHE PAS");
        System.out.println(approximatePi(n));
    }
}