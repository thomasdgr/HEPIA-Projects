interface Pushable {
    void push();
  }
  
public class Test {
    public static void push(Pushable p) {
        p.push();
        System.out.println("Button has been pushed");
    }
    
    public static void main(String[] args) {
        push( new Pushable(){
            public void push() { System.out.println("Push 1"); }
        } ); 
    
        push( () -> System.out.println("Push 2") ); 
    }
}  