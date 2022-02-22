import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class App {
    public static boolean isNumeric(String term){
        term = term.trim();
	    try {
            int i = Integer.parseInt(term);
        } catch (NumberFormatException nfe) {
            return false;
        }
        return true;
    }
    public static int[] indexes(String term, char c){
        String tmp = term.replace(String.valueOf(c), "");
        char[] arrayS = term.toCharArray();
        int[] res = new int[arrayS.length - tmp.length()];
        int j = 0;
        for(int i = 0; i < arrayS.length; i++){
            if (Character.compare(arrayS[i], c) == 0){
                res[j] = i;
                j++;
            }
        }
        return res;
    }
    public static boolean isUpper(String term){
        String res = term.toUpperCase();
        return term.compareTo(res) == 0;
    }
    public static String sorted(String term){
        char tmp[] = term.toCharArray();
        Arrays.sort(tmp);
        return String.valueOf(tmp);
    }
    public static void main(String[] args){
        System.out.println(isNumeric("42"));
        System.out.println(isNumeric("  22 "));
        System.out.println(isNumeric("  -33   "));
        System.out.println(isNumeric(" 22.0"));
        System.out.println(isNumeric(" 2f3"));

        int[] res = indexes("maison", 'i');
        System.out.print("maison, i -> {");
        for(int i = 0; i < res.length; i++){
            if(res[i] != 0){
                System.out.print(res[i] + ",");
            }
        }
        System.out.println("}");

        res = indexes("tralala", 'a');
        System.out.print("tralala, a -> {");
        for(int i = 0; i < res.length; i++){
            if(res[i] != 0){
                System.out.print(res[i] + ",");
            }
        }
        System.out.println("}");

        res = indexes("coucou", 'x');
        System.out.print("coucou, x -> {");
        for(int i = 0; i < res.length; i++){
            if(res[i] != 0){
                System.out.print(res[i] + ",");
            }
        }
        System.out.println("}");

        System.out.println(isUpper("ABC"));
        System.out.println(isUpper("AbC"));

        System.out.println(sorted("lkjlkjKJk9"));
    }
}
