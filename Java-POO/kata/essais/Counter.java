import java.util.Objects;

public class Counter {

    private int count;
    
    public Counter(){
        this.SetValue(0);
    }

    public void SetValue(int value){
        this.count = value;
    }

    public void Click(){
        this.count = (this.count + 1) % 10000;
    }

    public int CurrentCount(){
        return this.count;
    }

    @Override
    public String toString(){
        return this.fourDigits(this.count);
    }

    public String fourDigits(int number){
        return String.format("%04d", number).substring(0, 4);
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

    public void Reset(){
        this.SetValue(0);
    }


    public static void main(String[] args){
        Counter counter1 = new Counter();
        System.out.println(counter1.toString());

        for(int i = 0; i < 150; i++){
            counter1.Click();
        }
        System.out.println(counter1.toString());

        Counter counter2 = new Counter();
        counter2.SetValue(150);

        Counter counter3 = new Counter();
        counter3.SetValue(0);
        
        System.out.print("Counters 1 and 2 ");
        System.out.println( counter1.equals(counter2) ? "are equals" : "are not equals");
        System.out.print("Counters 1 and 3 ");
        System.out.println( counter1.equals(counter3) ? "are equals" : "are not equals");

        counter1.Reset();
        System.out.print("Counters 1 and 3 ");
        System.out.println( counter1.equals(counter3) ? "are equals" : "are not equals");
    }
}