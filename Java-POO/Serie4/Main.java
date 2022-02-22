import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Main{
    // ex 4.1
    /*   La fonction hashcode() retourne le hash d'un objet. Ce hash doit être le même si deux
     *   objets sont égaux. Si on a modifié le equals() mais pas le hashcode(), on pourrait avoir
     *   deux objets qui sont égaux sans que leur hash soit le même. Il faut donc aussi redéfinir
     *   le hashcode().
     */

    // ex 4.2
    public enum Day{
        Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday;
        
        public int dayOfWeek(){
            return this.ordinal()+1;
        }
    }

    // ex 4.3
    /*   Patient hérite de Person donc les objets de Patient sont des instances de Person.
     *   Dans le premier cas, instanceof() retourne true pour n'importe quel objet qui hérite
     *   de Person or on veut que ce soit un objet de type Person et ceci nous est garantit avec
     *   getClass() qui compart les types car deux objets sont égaux s'ils sont du même type.
     */

    // ex 4.4
    public enum Drink{

        BiereBlanche(4.5, 4.0, "Bière blanche"), BiereAmbree(5.2, 5.0, "Bière ambrée"),
        SodaCola(0, 3.5, "Soda Cola"), Whisky(57.0, 9.0, "Whisky");     

        private double alcoholLevel;
        private double price;
        private String name;

        private Drink(double alcoholLevel, double price, String name){
            this.alcoholLevel = alcoholLevel;
            this.price = price;
            this.name = name;
        }

        public Boolean isDrinkAlcoholic(){
            return this.alcoholLevel != 0;
        }

        public double alcoholLevel(){
            return this.alcoholLevel;
        }

        public double price(){
            return this.price;
        }

        public String nom(){
            return this.name;
        }

        @Override
        public String toString(){
            return this.name + " with " + this.alcoholLevel + "% of alcohol for only " + this.price + ".-";
        }
    }

    public static void verifyDrink(Drink d){
        System.out.println(d.toString());
        if(d.isDrinkAlcoholic()){
            System.out.print("\tContrôle d'âge nécessaire: ");
            if(d.alcoholLevel() < 6.0){
                System.out.println("Le taux est inférieur à 6.0%, la personne doit avoir 16 ans révolus");
            }else{
                System.out.println("Le taux est supérieur à 6.0%, la personne doit avoir 18 ans révolus");
            }
        } else{
            System.out.println("\tBravo");
        }
    }

    // ex 4.5
    /*   A: f(int)
     *   C: f(int)
     *   C: f(int)
     *   B: f(short)
     *   B: f(short)
     *   A: f(short)
     *   B: f(short)
     *   B: f(short)
     *   B: f(short)
     */

    // ex 4.6
    /*   1 -   redéfinition
     *         surcharge
     *         redéfinition
     *           
     *   2 -   invalide (changement de la valeur de retour), redéfinition
     *         valide, redéfinition
     *         valide, surcharge
     */
     
    // ex 4.7
    /*   erreur de compilation -> f(A a) n'existe pas
     *   B
     *   C
     *   erreur de compilation -> pas de classe pour créer un objet D
     *   erreur de compilation -> f(String s) n'existe pas
     */

    // ex 4.8
    /*   1 -   B: short
     *         A: short
     *         A: double
     *         A: double
     *         A: double
     *         A: double
     *         A: double
     *         A: double
     *   
     *   2 -   B bc = new C() provoque une erreur de compilation. En effet, bc est une référence   
     *         de type B (classe étendue de A) qui pointe sur un objet de type C (une autre classe
     *         étendue de A). De ce fait, on ne peut pas faire la convertion ce qui gènère une erreur.
     */        

    // ex 4.9
    /*   FAUX
     *   VRAI
     *   FAUX
     *   FAUX
     *   FAUX
     *   FAUX
     */

     // ex 4.10
    public static int[] append(int[] is, int nb){
        int[] res = new int[is.length+1];
        res[0] = nb;
        for(int i = 1; i <= is.length; i++){
            res[i] = is[i-1]; 
        }
        return res;
    }

     // main commun
    public static void main(String[] args){
        // ex 4.2
        for(Day d: Day.values() ){
            System.out.println(d + " is the day number: " + d.dayOfWeek());
        }
        System.out.println();
        
        // ex 4.4
        Drink d1 = Drink.Whisky;
        verifyDrink(d1);
        Drink d2 = Drink.SodaCola;
        verifyDrink(d2);   
        System.out.println();

        // ex 4.10
        int[] is = {1, 2, 2, -1, 5};
        int[] is2 = append(is, 10);
        for(int i = 0; i < is2.length; i++){
            System.out.println(is2[i]); 
        }
    }
}
