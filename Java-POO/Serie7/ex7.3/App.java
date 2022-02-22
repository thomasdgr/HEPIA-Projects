import java.util.Optional;
import java.util.function.Supplier;

public class App{
    public static Optional<Integer> test(Supplier<Integer> kek){
        try {
            return Optional.ofNullable(kek.get());
        } catch(Exception e){
            return Optional.empty();
        }
    }
    
    public static void main(String[] args) {
        Optional<Integer> t1 = test( () -> 3 );
        System.out.println(t1.get());
        Optional<Integer> t2 = test( () -> 3 + 4 );    
        System.out.println(t2.get());
        Optional<Integer> t3 = test( () -> 3 / 0 );    
        System.out.println(t3.isEmpty());
        Optional<Integer> t4 = test( () -> null );
        System.out.println(t4.isEmpty());
        Optional<Integer> t5 = test( () -> { throw new RuntimeException(); } );
        System.out.println(t5.isEmpty());
    }
}