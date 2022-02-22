import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Main { 
    public static List<Integer> doubleThat(List<Integer> is){
        List<Integer> result = new ArrayList<>();
        is.forEach( (data) -> result.add(data * 2));
        return result;
    }
    public static List<Integer> filterGreaterOrEqual(List<Integer> is, int value){
        List<Integer> result = new ArrayList<>();
        for (int elem : is) {
            if(elem >= value){
                result.add(elem);
            }
        }
        return result;
    }
    public static List<Integer> filterPositiveAndThenDoubleThem(List<Integer> is){
        List<Integer> result = filterGreaterOrEqual(is, 0);
        return doubleThat(result);
    }
    public static void main(String[] args){
        List<Integer> lst = new ArrayList<>();
        int size = 11;
        for(int i = 1; i < size; i++){
            lst.add(i);
        }

        List<Integer> reslut = doubleThat(lst);
        result.forEach( data -> System.out.println(data) );
        System.out.println();

        List<Integer> reslut2 = filterGreaterOrEqual(reslut, 8);
        result2.forEach( data -> System.out.println(data) );
        System.out.println();

        List<Integer> reslut3 = filterPositiveAndThenDoubleThem(reslut2);
        result3.forEach( data -> System.out.println(data) );
    }
    
}
