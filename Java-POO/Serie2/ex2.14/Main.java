import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Main {
    public static String removOccurrence(String s, char letter){
        return s.replaceAll(String.valueOf(letter), s);
    }
    public static String removFirstOccurrence(String s, char letter){
        return s.replaceFirst(String.valueOf(letter), "");
    }
    public static Boolean contains(String s, char letter){
        return s.contains(String.valueOf(letter));
    }
    public static String removeAll(String s, char letter){
        if(contains(s, letter)){
            s = removFirstOccurrence(s, letter);
            return removeAll(s, letter);
        }
        return s;
    }
    public static void main(String[] args){
        System.out.println(removFirstOccurrence("abracadabra", 'a'));
        System.out.println(removFirstOccurrence("babar", 'r'));
        System.out.println(removFirstOccurrence("babar", 'z'));
        System.out.println(removFirstOccurrence("", 'r'));
        System.out.println();

        System.out.println(contains("babar", 'z'));
        System.out.println(contains("babar", 'a'));
        System.out.println(contains("", 'a'));
        System.out.println();

        System.out.println(removeAll("abracadabra", 'a'));
    }    
}
