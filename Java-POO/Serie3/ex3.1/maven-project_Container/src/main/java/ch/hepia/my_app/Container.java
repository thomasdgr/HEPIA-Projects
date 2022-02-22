package ch.hepia.my_app;
import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Container {

    // ex3.1.1
    public static List<Integer> transfer(int origine, int firstDest, int ...destinations) {
        List<Integer> res = new ArrayList<>();
        
        List<Integer> destinationsList = new ArrayList<>();
        destinationsList.add(firstDest);
        for (int i : destinations){
            destinationsList.add(i);
        }

        int reste = origine;
        
        for (int dst : destinationsList) {
            if(reste - dst < 0){
                dst = reste;
                reste = 0;
            }
            if(reste > 0){
                reste = reste - dst;
            }
            res.add(dst);
        }
        return res;
    }

    // ex3.1.2
    private int max_size;
    private int crt_size;

    public Container(int size){
        checkPositive(size);
        this.max_size = size;
        this.crt_size = 0;
    }

    public void checkPositive(int value){
        if(value <= 0){
            throw new RuntimeException("size must be greater than 0");
        }
    }

    public static Container withCapacity(int size){
        Container c = new Container(size);
        return c;
    }

    public void fillToTheMax(){
        this.crt_size = this.max_size;
    }

    public void fillWith(int size){
        checkPositive(size);
        this.crt_size = size;
    }

    public void fillTo(Container ... destinations){
        if(destinations.length < 1){
            throw new RuntimeException("Need to give at least one destination container");
        }
        int reste = this.crt_size;
        for (Container dst : destinations) {
            if(reste - dst.max_size < 0){
                dst.crt_size = reste;
                reste = 0;
            }
            if(reste > 0){
                reste = reste - dst.max_size;
                dst.crt_size = dst.max_size;
            }
        }
        this.crt_size = 0;
    }

    public Boolean isFull(){
        return this.crt_size == this.max_size;
    }

    public int remaining(){
        return this.max_size - this.crt_size;
    }

    public void remove(int value){
        if(this.crt_size - value < 0){
            throw new RuntimeException("Amount to remove can't exceed amount of the input container");
        }
        this.crt_size = this.crt_size - value;
    }

    public int quantity(){
        return this.crt_size;
    }

    public void flush(){
        this.crt_size = 0;
    }

    @Override
     public String toString(){
         return "(Container: " + this.crt_size + "/" + this.max_size + ")";
     }

    public static void main(String[] args){
        Container origin = Container.withCapacity(10);
        origin.fillToTheMax();
            
        Container destination1 = new Container(5);
        destination1.fillWith(2);
            
        Container destination2 = Container.withCapacity(3);
            
        Container destination3 = Container.withCapacity(10);

        System.out.println("origin: " + origin.toString());
        origin.fillTo(destination1, destination2, destination3);

        System.out.println("new origin: " + origin.toString());
        System.out.println("dest 1: " + destination1.toString());
        System.out.println("dest 2: " + destination2.toString());
        System.out.println("dest 3: " + destination3.toString());
            
        System.out.println(destination1.isFull() ? "dest1 is full" : "dest1 is not full");

        System.out.println(destination2.isFull() ? "dest2 is full" : "dest2 is not full");
            
        System.out.println(destination3.isFull() ? "dest3 is full" : "dest3 is not full");
        
        destination2.remove(2);
        System.out.println("new dest 2: " + destination2.toString());
        System.out.println("quantity of dest 2: " + destination2.quantity());

        destination3.flush();
        System.out.println("new dest 3: " + destination3.toString());
        System.out.println("dest 3 remaining: " + destination3.remaining());
    }
}

