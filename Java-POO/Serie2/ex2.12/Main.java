import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Main {
    public static int countPositive(double[][] array){
        int result = 0;
        for (double[] elemLst : array) {
            for (double o : elemLst) {
                if(o >= 0.0){
                    result++;
                }
            }
        }
        return result;
    }
    public static void main(String[] args){
        double[][] example = {
            {1.0, -2.0},
            {3.0},
            {1.5, -2.5, 3.0}    
        };
        int res = countPositive(example);
        System.out.println("Count: " + res);
    }    
}
