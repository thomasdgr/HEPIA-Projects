import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Main {
    public static double sum(double[][] array){
        double result = 0;
        for (double[] elemLst : array) {
            for (double o : elemLst) {
                result = result + o;
            }
        }
        return result;
    }
    public static void main(String[] args){
        double[][] example = {
            {1.0, 2.0},
            {3.0},
            {1.5, 2.5, 3.0}    
        };
        double res = sum(example);
        System.out.println("Sum: " + res);
    }    
}
