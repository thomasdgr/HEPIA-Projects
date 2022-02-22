import java.util.*;

public class App{
    public static void main(String[] args) {
        Box<Integer> box1 = new Box<>(1);
        Box<Integer> box2 = new Box<>(2);

        System.out.println( box1 );
        System.out.println( box2 );
        System.out.println( box1.equals(box2) );
        System.out.println( new Box<>(3) );
        System.out.println( box1.get() );

        System.out.println(box1.compareTo(box2));
        System.out.println(Util.isBigger(box1,box2));
    }
}