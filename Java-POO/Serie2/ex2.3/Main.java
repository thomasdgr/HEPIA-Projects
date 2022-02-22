import java.lang.Math;

public class Main{

    public static void printTriangle(int n){
        String display = "";
        for(int i = 1; i <= n; i++){
            display = display + "*";
            System.out.println(display);
        }
    }

    public static void main(String[] args){
        printTriangle(4);
    }
}