import java.util.*;

public class App{

    public enum Drink{
        Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday;

        public int dayOfWeek(){
            return this.ordinal() + 1;
        }
    }

    public static void main(String[] args) {
        for(Day d : Day.values() ){
            System.out.println(d + " is the day number: " + d.dayOfWeek());
        }
    }
}