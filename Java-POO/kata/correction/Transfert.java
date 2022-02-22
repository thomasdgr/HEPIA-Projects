import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Transfert {

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

    public Transfert(int size){
        checkPositive(size);
        this.max_size = size;
        this.crt_size = 0;
    }

    public void checkPositive(int value){
        if(value <= 0){
            throw new RuntimeException("size must be greater than 0");
        }
    }

    public static Transfert withCapacity(int size){
        Transfert c = new Transfert(size);
        return c;
    }

    public void fillToTheMax(){
        this.crt_size = this.max_size;
    }

    public void fillWith(int size){
        checkPositive(size);
        this.crt_size = size;
    }

    public void fillTo(Transfert ... destinations){
        if(destinations.length < 1){
            throw new RuntimeException("Need to give at least one destination Transfert");
        }
        int reste = this.crt_size;
        for (Transfert dst : destinations) {
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
            throw new RuntimeException("Amount to remove can't exceed amount of the input Transfert");
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
         return "(Transfert: " + this.crt_size + "/" + this.max_size + ")";
     }

    public static void main(String[] args){
        Transfert origin = Transfert.withCapacity(10);
        origin.fillToTheMax();
            
        Transfert destination1 = new Transfert(5);
        destination1.fillWith(2);
            
        Transfert destination2 = Transfert.withCapacity(3);
            
        Transfert destination3 = Transfert.withCapacity(10);

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

