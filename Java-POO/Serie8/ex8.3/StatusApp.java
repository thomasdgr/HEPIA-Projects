import java.util.*;

public class StatusApp{
    public static void log(Object o){
        System.out.println(o);
    }
    public static Status<Integer, String> random(){
        int chance = new Random().nextInt(3);
        if(chance == 0){
            return Status.onWith(42);
        } else{
            return chance == 1 ? Status.off() : Status.errorWith("Oups");
        }
    }
    public static void main(String[] args){
        Status<Integer, String> s = random();
        if(s.isOn()){
            log("Status On: " + s.get());
        } else if(s.isError()){
            log("Status Unstable: " + s.getError());
        } else{
            log("Status Off");
        }
        s.accept(
            i -> log("Status On: " + i) ,
            () -> log("Status Off"),
            e -> log("Status Unstable: " + e)
        );
    }
}