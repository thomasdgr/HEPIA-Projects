import java.util.Optional;
import java.util.function.Consumer;
import java.util.List;
import java.util.ArrayList;

public interface IntegerStack{
    int pop();

    default public Optional<Integer> popOption(){
        try{
            return Optional.of(this.pop());
        } catch(EmptyIntegerStack e){
            return Optional.empty();
        }
    }

    default public void ifHeadIsPresent(Consumer<Integer> consumer){
        int res = this.peek();
        consumer.accept(res);
    }
    
    void push(int i);
    
    int size();
    
    int peek();
    
    default public Optional<Integer> peekOption(){
        try{
            return Optional.of(this.peek());
        } catch(EmptyIntegerStack e){
            return Optional.empty();
        }
    }

    default public boolean isEmpty(){
        return this.size() == 0;
        // return peekOption().isEmpty();

        /*Optional<Integer> value = popOption();
        if(value.isPresent()){
            push(value.get());
            return false;
        }
        return true;*/
    }
}