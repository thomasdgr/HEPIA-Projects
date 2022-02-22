public class Something implements MaybeInt {
    
    private int value;
    
    public Something(int i){
        this.value = i;
    }

    public boolean exists(){
        return true;
    }

    public int get(){
        return this.value;
    }
}