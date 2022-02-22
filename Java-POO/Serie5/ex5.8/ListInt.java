/**
 * Exercice 5.8
 * (exercice de groupe sur la classe ListInt)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

public interface ListInt{

  public void insert(int i);

  default public void insertAll(int... array){
    for (int i : array){
      this.insert(i);
    }
  }

  public int get(int i);

  default public boolean isEmpty(){
    return this.size() == 0;
  }

  public int size();

  public int numberOfElements();

  public void clear();

}
