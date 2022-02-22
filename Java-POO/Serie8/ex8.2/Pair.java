import java.util.Objects;
import java.util.function.Function;

public class Pair<T,R> {

    private T leftValue;
    private R rightValue;

    public Pair(T t1, R t2){
        this.leftValue = t1;
        this.rightValue = t2;
    }

    public T leftValue(){
        return this.leftValue;
    }

    public R rightValue(){
        return this.rightValue;
    }

    @Override
    public String toString(){
        return "Pair(" + this.leftValue.toString() + "," + this.rightValue.toString() + ")";
    }

    @Override
    public boolean equals(Object o){
        if(this == o){
            return true;
        }
        if(o == null || o.getClass() != this.getClass()){
            return false;
        }
        Pair<?,?> other = (Pair<?,?>)o;
        return (this.leftValue.equals(other.leftValue)) && (this.rightValue.equals(other.rightValue));
    }

    @Override
    public int hashCode(){
        return Objects.hash(this.leftValue);
    }

    public <R> Pair<T,R> mapLeftValue(Function<T,T> f) {
        return new Pair<T,R>(f.apply(this.leftValue), (R)this.rightValue);
    }

    public <R> Pair<T,R> mapRightValue(Function<R,R> f) {
        return new Pair<T,R>(this.leftValue, f.apply((R)this.rightValue));
    }
}