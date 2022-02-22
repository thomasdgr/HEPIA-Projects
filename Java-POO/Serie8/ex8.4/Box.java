import java.util.Objects;
import java.util.function.*;

public final class Box<T extends Comparable<T>> implements Comparable<Box<T>>{

    private T value;

    public Box(T value){
        this.value = value;
    }

    public T get(){
        return this.value;
    }

    public void set(T newValue){
        this.value = newValue;
    }

    @Override
    public String toString(){
        return "[" + this.value.toString() + "]";
    }

    @Override
    public boolean equals(Object o){
        if (this == o){
            return true;
        }
        if (o == null || o.getClass() != this.getClass()){
            return false;
        }
        Box<?> other = (Box<?>)o;
        return this.value.equals(other.value);
    }

    @Override
    public int hashCode(){
        return Objects.hash(this.value);
    }
    
    public <R extends Comparable<R>> Box<R> map(Function<T, R> f) {
        return new Box<R>(f.apply(this.value));
    }

    public int compareTo(Box<T> b){
        return this.value.compareTo(b.get());
    }
}

class Util{
    public static <T extends Comparable<T>> Boolean isBigger(Box<T> b1, Box<T> b2){
        return b1.compareTo(b2) > 0;
    }
}
