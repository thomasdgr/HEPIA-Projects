public interface ListInt extends Iterable<Integer>{

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

  public void clear();

}
