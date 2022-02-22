import java.util.Optional;
import java.util.function.Consumer;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

public class App{
    public static void main(String[] args) {
        ListInt list = new LinkedListInt();
        
        System.out.print("before insert, list is ");
        System.out.println(list.isEmpty() ? "empty" : "not empty");
    
        list.insert(1);
        list.insertAll(2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
    
        System.out.print("after insert, list is ");
        System.out.println(list.isEmpty() ? "empty" : "not empty");

        // print classique
            //list.printLinkedListInt();
        
        // print bof
            /*Iterator<Integer> it = list.iterator();
            while(it.hasNext()){
                System.out.println("\tValue: " + it.next());
            }*/
        
        // print cool
        list.forEach(v -> System.out.print(v + ","));

        System.out.println("\nnumber of elements = " + list.size());
        System.out.println("head = " + list.headValue());

        int i = 4;
        System.out.println("element at index " + i + " = " + list.get(i));
    
        list.clear();
        System.out.print("after clear, list is ");
        System.out.println(list.isEmpty() ? "empty" : "not empty");
    }
}