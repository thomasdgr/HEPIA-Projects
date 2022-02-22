import java.util.Objects;

public class Counter {
    private int count;

    public Counter(){
        this.setValue(0);        
    }

    public void click(){
        this.setValue(this.count+1);        
    }

    public void reset(){
        this.setValue(0);        
    }

    public int currentValue(){
        return this.count;
    }

    public void setValue(int newValue){
        this.count = newValue % 10000;
    }

    private String convertToFourDigits(int nb){
        return String.format("%04d", nb).substring(0, 4);
    }

    @Override
    public String toString(){
        return "Counter: value = " + convertToFourDigits(this.count);
    }

    @Override
    public boolean equals(Object o){
        if(this == o){
            return true;
        } 
        Counter other = (Counter) o;
        if(o == null || o.getClass() != this.getClass() || other.hashCode() != this.hashCode()){
            return false;
        } 
        return this.count == other.count;
    }

    @Override
    public int hashCode(){
        return Objects.hash(this.count);
    }

    public static void main(String[] args){
        Counter counter1 = new Counter();
        System.out.println(counter1.toString());

        for(int i = 0; i < 150; i++){
            counter1.click();
        }
        System.out.println(counter1.toString());

        Counter counter2 = new Counter();
        counter2.setValue(150);

        Counter counter3 = new Counter();
        counter3.setValue(0);
        
        System.out.print("Counters 1 and 2 ");
        System.out.println( counter1.equals(counter2) ? "are equals" : "are not equals");
        System.out.print("Counters 1 and 3 ");
        System.out.println( counter1.equals(counter3) ? "are equals" : "are not equals");

        counter1.reset();
        System.out.print("Counters 1 and 3 ");
        System.out.println( counter1.equals(counter3) ? "are equals" : "are not equals");
    }
}