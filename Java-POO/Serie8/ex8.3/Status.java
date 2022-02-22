import java.util.function.*;
import java.util.*;

public class Status<T,R> {

    private final T number;
    private final R errorMessage;

    public Status(T i, R s){
        this.number = i;
        this.errorMessage = s;
    }

    public static Status onWith(Object newNumber){
        return new Status(newNumber, "on");
    }

    public static Status off(){
        return new Status(0, "off");
    }

    public static Status errorWith(Object newErrorMessage){
        return new Status(-1, newErrorMessage);
    }

    public T get(){
        return this.number;
    }

    public R getError(){
        return this.errorMessage;
    }

    public Boolean isOn(){
        return (Integer)this.get() > 0;
    }

    public Boolean isOff(){
        return (Integer)this.get() == 0;
    }

    public Boolean isError(){
        return (Integer)this.get() == -1;
    }

    public void accept(Consumer<T> f1, Runnable s1, Consumer<R> f2){
        if(isOn()){
            f1.accept(get());
        } else if(isError()){
            f2.accept(getError());
        } else{
            s1.run();
        }   
    }
}