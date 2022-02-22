import java.util.*;

public class App{
    public static void main(String[] args) {
        Pair<Integer,String> kek = new Pair<>(2,"kek");
        System.out.println(kek.toString());
        
        Pair<Integer,String> kek2 = kek.mapLeftValue( i -> i+1 );
        System.out.println(kek2.toString());

        kek2 = kek.mapRightValue( s -> s.toUpperCase() );
        System.out.println(kek2.toString());

        Pair<Boolean,List<String>> kek3 = new Pair<>(true, new ArrayList<>(List.of("k","e","k")));
        System.out.println(kek3.toString());

        Pair<Integer,Double> kek4 = new NumberPair<>(10,10.0);
        System.out.println(kek4.toString());

        // pas de vérification que les types soient les memes
        Pair<Integer,Integer> kek5 = new UniquePair<>(10,10);
        System.out.println(kek5.toString());
    }    
}