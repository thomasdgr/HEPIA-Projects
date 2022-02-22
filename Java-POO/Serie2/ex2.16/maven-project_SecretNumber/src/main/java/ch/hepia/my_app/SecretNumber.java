package ch.hepia.my_app;
import java.util.Scanner;
import java.lang.Math;

public class SecretNumber {
    public static double normalize(double value, double minSource, double maxSource, double minTarget, double maxTarget){
        return (((value - minSource) * (maxTarget - minTarget)) / (maxSource - minSource)) + minTarget;
    }
    public static int randomInt(int minValue, int maxValue){
        return (int)normalize(Math.random(), 0, 1, minValue, maxValue);
    }
    public static void userGuessNumber(int numberToFind, int N, Scanner sc){
        int nb = 0;
        int count = 0;
        while(nb != numberToFind){
            System.out.print("Enter number: ");
            while(!sc.hasNextInt()){
                System.out.println("This is not a valid number !");
                System.out.print("Enter number: ");
                sc.next();
            }
            nb = sc.nextInt();   
            if(nb < 1 || nb > N){
                System.out.println("number is not between 1 and " + N);
                System.out.print("Enter number: ");
                sc.next();
            } else {
                count++;
                if(nb < numberToFind){
                    System.out.println("number to guess is greater");
                } else if(nb > numberToFind){
                    System.out.println("number to guess is lower");
                }
            }
        }
        System.out.println("Congratulations, you found the number in " + count + " attempts");
    }
    public static void machineGuessNumber(int N, Scanner sc){
        int crt = N/2;
        String tmp = "";
        int count = (int)Math.round(Math.log(N)) + 1;
        while(true){
            System.out.print("Is your number " + crt + " ? [o/+/-]:");
            tmp = sc.next();
            if(tmp.equals("+")){
                crt = crt + (int) Math.pow(2, count);
                count--;
            } else if(tmp.equals("-")){
                crt = crt - (int) Math.pow(2, count);
                count--;
            } else if(tmp.equals("o")){
                break;
            } else{
                System.out.print("Please choose between [o/+/-]:");
                tmp = sc.next();
                if(tmp.equals("o")){
                    break;
                }
            }
        }
        System.out.println("YEEEPI IA is definatly better than human");
    }

    public static void main(String[] args){
        int N = 0;
        String arg = "guess";
        try {
            if(arg.compareTo(args[0]) == 0){
                N = Integer.parseInt(args[1]);
            } else{
                N = Integer.parseInt(args[0]);
            }
        } catch (NumberFormatException e){
            System.out.println("=================================================================================\n");
            System.out.println("Wrong arguments, usage:");
            System.out.println("-> IA guess your number : mvn:exec -Dexec.args=\"<guess> <max range (greater than 1)>\"");
            System.out.println("-> YOU guess IA's number: mvn:exec -Dexec.args=\"<max range (greater than 1)>\"");
            System.out.println("\n=================================================================================");
            System.exit(0);
        }
        Scanner sc = new Scanner(System.in);
        if(arg.compareTo(args[0]) == 0){
            System.out.println("\n");
            machineGuessNumber(N, sc);
            System.out.println("\n");
        } else {
            int numberToFind = randomInt(1, N);
            System.out.println("\n");
            //System.out.println("hint : number to guess is between " + numberToFind + " and " + numberToFind);
            userGuessNumber(numberToFind, N, sc);
            System.out.println("\n");
        }
    }
}
