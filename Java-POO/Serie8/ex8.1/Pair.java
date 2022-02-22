import java.util.Objects;
import java.util.function.Function;

public final class Pair<T,R> {

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

    public <T2> Pair<T2,R> mapLeftValue(Function<T,T2> f){
        return new Pair<>(f.apply(this.leftValue), this.rightValue);
    }

    public <R2> Pair<T,R2> mapRightValue(Function<R,R2> f){
        return new Pair<>(this.leftValue, f.apply(this.rightValue));
    }

    public <T2,R2> Pair<T2,R2> mapBothValues(Function<T,T2> f1, Function<R,R2> f2){
        return new Pair<>(f1.apply(this.leftValue), f2.apply(this.rightValue));
    }
}