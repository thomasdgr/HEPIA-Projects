import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Transfert {

    private int crt_size;
    private int max_size;

    public Transfert(int capacity){
        CheckPositive(capacity);
        this.crt_size = 0;
        this.max_size = capacity;
    }

    public void CheckPositive(int number){
        if(number <= 0){
            throw new RuntimeException("capacity must be greater than 0");
        }
    }

    public static Transfert WithCapacity(int capacity){
        return new Transfert(capacity);
    }

    public void FillToTheMax(){
        this.crt_size = this.max_size;
    }

    public void FillWith(int number){
        CheckPositive(number);
        if(this.crt_size + number > this.max_size){
            throw new RuntimeException("size exceed capacity while filling " + number);
        }
        this.crt_size = this.crt_size + number;
    }

    @Override
    public String toString(){
        return "transfert : " + this.crt_size + "/" + this.max_size;
    }

    public void FillTo(Transfert ... destinations){
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

    public Boolean IsFull(){
        return this.crt_size == this.max_size;
    }

    public void Remove(int number){
        CheckPositive(number);
        if(this.crt_size - number < 0){
            throw new RuntimeException("can't remove more than current size");
        }
        this.crt_size = this.crt_size - number;
    }

    public int Remaining(){
        return this.max_size - this.crt_size;
    }

    public int Quantity(){
        return this.crt_size;
    }

    public void Flush(){
        this.crt_size = 0;
    }

    public static void main(String[] args){
        Transfert origin = Transfert.WithCapacity(10);
        origin.FillToTheMax();
            
        Transfert destination1 = new Transfert(5);
        destination1.FillWith(2);
            
        Transfert destination2 = Transfert.WithCapacity(3);
            
        Transfert destination3 = Transfert.WithCapacity(10);

        System.out.println("origin: " + origin.toString());
        origin.FillTo(destination1, destination2, destination3);

        System.out.println("new origin: " + origin.toString());
        System.out.println("dest 1: " + destination1.toString());
        System.out.println("dest 2: " + destination2.toString());
        System.out.println("dest 3: " + destination3.toString());
            
        System.out.println(destination1.IsFull() ? "dest1 is full" : "dest1 is not full");

        System.out.println(destination2.IsFull() ? "dest2 is full" : "dest2 is not full");
            
        System.out.println(destination3.IsFull() ? "dest3 is full" : "dest3 is not full");
        
        destination2.Remove(2);
        System.out.println("new dest 2: " + destination2.toString());
        System.out.println("Quantity of dest 2: " + destination2.Quantity());

        destination3.Flush();
        System.out.println("new dest 3: " + destination3.toString());
        System.out.println("dest 3 Remaining: " + destination3.Remaining());
    }
}

