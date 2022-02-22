import java.util.Optional;
import java.util.function.Consumer;
import java.util.List;
import java.util.ArrayList;

public class App{
    public static void main(String[] args) {
        IntegerStack stack = new IntegerArrayStack();
        stack.push(1);
        stack.push(2);
        stack.push(3);

        stack.ifHeadIsPresent(v -> System.out.println("head: " + v) );
        
        int res = stack.pop();
        System.out.println("value poped: " + res);
        
        stack.ifHeadIsPresent(v -> System.out.println("head: " + v) );
        
        Optional<Integer> result = stack.popOption();
        System.out.println("value poped: " + result.get());
        
        result = stack.peekOption();
        System.out.println("head: " + result.get());
        stack.pop();
        
        // test no error
        result = stack.popOption();
        stack.peekOption();
    }
}