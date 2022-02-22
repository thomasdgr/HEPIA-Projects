import java.util.Optional;
import java.util.function.Consumer;
import java.util.List;
import java.util.ArrayList;

public interface GenericStack<T>{
    T pop();

    default public Optional<T> popOption(){
        try{
            return Optional.of(this.pop());
        } catch(EmptyStack e){
            return Optional.empty();
        }
    }

    default public void ifHeadIsPresent(Consumer<T> consumer){
        T res = this.peek();
        consumer.accept(res);
    }
    
    void push(T value);
    
    int size();
    
    T peek();
    
    default public Optional<T> peekOption(){
        try{
            return Optional.of(this.peek());
        } catch(EmptyStack e){
            return Optional.empty();
        }
    }

    default public boolean isEmpty(){
        return this.size() == 0;
    }
}