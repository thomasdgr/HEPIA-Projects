public class Nothing implements MaybeInt {
    
    public Nothing(){ }
    
    public boolean exists(){
        return false;
    }

    public int get(){
        throw new RuntimeException("can't call get() on Nothing object");
    }
}