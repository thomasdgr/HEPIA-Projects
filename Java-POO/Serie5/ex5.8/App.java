/**
 * Exercice 5.8
 * (exercice de groupe)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

public class App{
  public static void main(String[] args) {
    ListInt list = new ArrayListInt();
    list.insert(0);
    list.insert(3);
    list.insertAll(2,1); // insertAll prend un nombre arbitraire d'éléments

    System.out.println( "Size: " + list.numberOfElements() );

    for(int i = 0; i < list.numberOfElements(); i+=1) {
      int v = list.get(i);
      System.out.println("Value: " + v);
    }
  
    list.clear();
    System.out.println( "Size: " + list.numberOfElements() );

  /*
  * Cet exemple afficherait
  * Size: 4
  * Value: 0
  * Value: 3
  * Value: 2
  * Value: 1
  * Size: 0
  */
  }
}
