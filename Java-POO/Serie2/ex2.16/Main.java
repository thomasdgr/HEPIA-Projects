import java.util.Scanner;
import java.lang.Math;

public class Main {
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
            System.out.print("Entrer un nombre: ");
            while(!sc.hasNextInt()){
                System.out.println("Ceci n'est pas un nombre !");
                System.out.print("Entrer un nombre: ");
                sc.next();
            }
            nb = sc.nextInt();   
            if(nb < 1 || nb > N){
                System.out.println("Le nombre n'est pas compris entre 1 et " + N);
                System.out.print("Entrer un nombre: ");
                sc.next();
            } else {
                count++;
                if(nb < numberToFind){
                    System.out.println("Le nombre à trouver est plus grand");
                } else if(nb > numberToFind){
                    System.out.println("Le nombre à trouver est plus petit");
                }
            }
        }
        System.out.println("Bravo vous avez trouvé le nombre en " + count + " essais");
    }
    public static void machineGuessNumber(int N, Scanner sc){
        int crt = N/2;
        String tmp = "";
        int count = (int)Math.round(Math.log(N)) + 1;
        while(true){
            System.out.print("S'agit-il du " + crt + " ? [o/+/-] :");
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
                System.out.print("Choisir entre [o/+/-] svp :");
                tmp = sc.next();
                if(tmp.equals("o")){
                    break;
                }
            }
        }
        System.out.println("YOUPIE, l'IA bat définitivement l'humain");
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
            System.out.println("Le paramètre donnée dans la commande doit etre un entier superieur à 1");
            System.exit(0);
        }
        Scanner sc = new Scanner(System.in);
        if(arg.compareTo(args[0]) == 0){
            machineGuessNumber(N, sc);
        } else {
            int numberToFind = randomInt(1, N);
            System.out.println("1 - " + N + " -> " + numberToFind);
            userGuessNumber(numberToFind, N, sc);
        }
    }
}
