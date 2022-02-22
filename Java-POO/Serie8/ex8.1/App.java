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

        Pair<Integer,Integer> kek4 = new Pair<>(1,2);
        Pair<Double,Double> kek5 = kek4.mapBothValues( a -> Double.valueOf(a), b -> Double.valueOf(b) );
        System.out.println(kek5.toString());
    }    
}