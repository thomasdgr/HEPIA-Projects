/**
 * Exercice 5.8
 * (exercice de groupe sur la classe ArrayListInt)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

public class ArrayListInt implements ListInt{
  private int[] array;
  private int numberOfElements;

  public ArrayListInt(){
    this.array = new int[10];
    this.numberOfElements = 0;
  }

  private void resize(int newSize){
    int[] newArray = new int[newSize];
    
    for (int i = 0; i < this.numberOfElements; i+=1){
      newArray[i] = this.array[i];
    }

    this.array = newArray;

    if(this.numberOfElements > this.array.length){
      this.numberOfElements = this.array.length;
    }
  }

  @Override
  public void insert(int i){
    if(this.numberOfElements == this.array.length){
      this.resize(this.numberOfElements + 10);
    }
    this.array[numberOfElements] = i;
    this.numberOfElements+=1;
  }

  @Override
  public int get(int i){
    if(i < this.numberOfElements){
      return this.array[i];
    }
    throw new RuntimeException("L'indice est trop grand!");
  }

  public int size(){
    return this.array.length;
  }

  public int numberOfElements(){
    return this.numberOfElements;
  }

  public void clear(){
    this.array = new int[0];
    this.numberOfElements = 0;
  }

}
