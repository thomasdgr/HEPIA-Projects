import java.util.Optional;
import java.util.function.Consumer;
import java.util.List;
import java.util.ArrayList;

public class IntegerArrayStack implements IntegerStack{
    private ArrayList<Integer> array;

    public IntegerArrayStack(){
        this.array = new ArrayList<>(); 
    }

    @Override
    public int pop(){
        if(this.size() != 0){
            int res = this.peek();
            this.array.remove(0);
            return res;
        }
        throw new EmptyIntegerStack();
    }

    @Override
    public void push(int i){
        this.array.add(0,i);
    }

    @Override
    public int size(){
        return this.array.size();
    }

    @Override
    public int peek(){
        if(this.size() != 0){
            return this.array.get(0);
        }
        throw new EmptyIntegerStack();
    }
}