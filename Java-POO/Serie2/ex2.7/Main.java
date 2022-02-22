import java.lang.Math;
import java.util.Scanner;

public class Main{

    public static int snakeGame(int currentSize, int n){
        currentSize = currentSize + n;
        if(currentSize == 0){
            System.out.println("Au revoir !");
            return 0;
        }
        for(int i = 0; i < currentSize-1; i++){
            System.out.print("*");
        }
        System.out.print("(^^)");
        System.out.println();
        return currentSize;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String tmp = "";
        int currentSize = 1;
        snakeGame(currentSize, 0);
        while(true){
            System.out.print("Direction [+/-] :");
            tmp = sc.next();
            if(tmp.equals("+")){
                currentSize = snakeGame(currentSize, 1);
            } else if(tmp.equals("-")){
                currentSize = snakeGame(currentSize, -1);
            } else{
                System.out.println("Choisir entre [+/-] svp");
            }
            if(currentSize == 0){
                System.exit(0);
            }
        }
    }
}