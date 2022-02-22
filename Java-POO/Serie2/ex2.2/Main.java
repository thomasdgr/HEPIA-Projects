import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Main{
    public static double minMaxRange(double value, double minValue, double maxValue){
        return Math.min(Math.max(minValue, value), maxValue);
    }
    public static double normalize(double value, double minSource, double maxSource, double minTarget, double maxTarget){
        return (((value - minSource) * (maxTarget - minTarget)) / (maxSource - minSource)) + minTarget;
    }
    public static double randomDouble(double minValue, double maxValue){
        return normalize(Math.random(), 0, 1, minValue, maxValue);
    }
    public static int randomInt(int minValue, int maxValue){
        return (int)(randomDouble(minValue, maxValue));
    }
    public static List<Double> randomListDouble(int nb, int minValue, int maxValue){
        List<Double> lst = new ArrayList<>();
        for(int i = 0; i < nb; i++){
            lst.add(randomDouble(minValue, maxValue));
        }
        return lst;
    }
    public static List<Integer> randomListInteger(int nb, int minValue, int maxValue){
        List<Integer> lst = new ArrayList<>();
        for(int i = 0; i < nb; i++){
            lst.add(randomInt(minValue, maxValue));
        }
        return lst;
    }
    public static double min(List<List<Double>>altitudes){
        double ref = altitudes.get(0).get(0);
        for (List<Double> lst : altitudes) {
            for (Object o : lst) {
                if((double)o < ref){
                    ref = (double)o;
                }
            }
        }
        return ref;

    }
    public static double max(List<List<Double>>altitudes){
        double ref = altitudes.get(0).get(0);
        for (List<Double> lst : altitudes) {
            for (Object o : lst) {
                if((double)o > ref){
                    ref = (double)o;
                }
            }
        }
        return ref;       
    }
    public static List<List<Double>> altitudeToShadesOfGray(List<List<Double>>altitudes){
        List<List<Double>> mat = new ArrayList<>();
        double min = min(altitudes);
        double max = max(altitudes); 
        for (List<Double> lst : altitudes) {
            List<Double> kek = new ArrayList<>();
            for (Object o : lst) {
                double data = normalize((double)o, min, max, 0.0, 255.0);
                kek.add(data);
            }
            mat.add(kek);
        }
        return mat;
    }

    public static void main(String[] args){

        System.out.println(minMaxRange(-4.3, 0.0, 3.0));
        System.out.println();

        System.out.println(randomDouble(10.0, 100.0));
        System.out.println();

        System.out.println(randomInt(10, 100));
        System.out.println();

        System.out.println(normalize(0.0, 0.0, 1.0, 500.0, 600.0));
        System.out.println(normalize(1.0, 0.0, 1.0, 500.0, 600.0));
        System.out.println(normalize(0.5, 0.0, 1.0, 500.0, 600.0));
        System.out.println(normalize(550, 500, 600, 0, 255));
        System.out.println();

        List<Double> lst1 = randomListDouble(10, 0, 10);
        lst1.forEach( data -> System.out.println(data) );
        System.out.println();
        
        List<Integer> lst2 = randomListInteger(10, 0, 10);
        lst2.forEach( data -> System.out.println(data) );
        System.out.println();

        int size = 3;
        List<List<Double>> altitudes = new ArrayList<>(size);
        for(int i = 0; i < size; ++i) {
            altitudes.add(randomListDouble(3, 0, 1000)); 
        }

        List<List<Double>> FiftyShadesOfGray = altitudeToShadesOfGray(altitudes);
        for (List<Double> elemLst : FiftyShadesOfGray) {
            elemLst.forEach(data -> System.out.println(data));
        }
    }
}