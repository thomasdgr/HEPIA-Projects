import java.util.Optional;
import java.util.function.Consumer;
import java.util.List;
import java.util.ArrayList;

public interface ListInt extends Iterable<Integer>{

    public void insert(int i);

    default public void insertAll(int firstNumber, int ... numbers){
        this.insert(firstNumber);
        for(int i : numbers){
            this.insert(i);
        }
    }
        
    public int get(int i);
    
    default public boolean isEmpty(){
        return this.size() == 0;
    }

    public Element FirstElement();
    
    default public int headValue(){
        return this.FirstElement().GetValueElem();
    }

    public int size();

    public void clear();

    public void printLinkedListInt();
}