import java.lang.Math;

public class Main{

    public static int factorielle(int n){
        int res = 0;
        if(n > 1){
            res = n * factorielle(n-1);
        } else {
            res = 1;
        }
        return res; 
    }

    public static void main(String[] args){
        int n = 8;
        System.out.println(n + "! = " + factorielle(n));
    }
}