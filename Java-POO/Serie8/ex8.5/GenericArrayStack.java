import java.util.Optional;
import java.util.function.Consumer;
import java.util.List;
import java.util.ArrayList;

public class GenericArrayStack<T> implements GenericStack<T>{
    private ArrayList<T> array;

    public GenericArrayStack(){
        this.array = new ArrayList<>(); 
    }

    @Override
    public T pop(){
        if(this.size() != 0){
            T res = this.peek();
            this.array.remove(0);
            return res;
        }
        throw new EmptyStack();
    }

    @Override
    public void push(T value){
        this.array.add(0,value);
    }

    @Override
    public int size(){
        return this.array.size();
    }

    @Override
    public T peek(){
        if(this.size() != 0){
            return this.array.get(0);
        }
        throw new EmptyStack();
    }
}