import java.util.Iterator;

public class App{
  public static void main(String[] args) {
    ListInt list = new ArrayListInt();
    list.insert(0);
    list.insert(3);
    list.insertAll(2,1); // insertAll prend un nombre arbitraire d'éléments

    System.out.println( "Size: " + list.numberOfElements());

    System.out.println( "\nTest 1:");
    for(int i = 0; i < list.numberOfElements(); i+=1) {
      int v = list.get(i);
      System.out.println("\tValue: " + v);
    }
    
    /* l'itérateur permet maintenant le code ci-dessous */
    System.out.println( "\nTest 2:");
    for (int v : list){
      System.out.println("\tValue: " + v);
    }

    /* ou */
    System.out.println( "\nTest 3:");
    Iterator<Integer> it = list.iterator();
    while(it.hasNext()){
      System.out.println("\tValue: " + it.next());
    }

    /* et même */
    System.out.println( "\nTest 4:");
    list.forEach(v -> System.out.println("\tValue: " + v));
  
    list.clear();
    System.out.println( "\nClear, Size: " + list.numberOfElements() );
  }
}
