import java.util.Objects;
import java.util.function.Function;

public class NumberPair<T extends Number, R extends Number> extends Pair {
    public NumberPair(T t1, R t2){
        super(t1,t2);
    }
}