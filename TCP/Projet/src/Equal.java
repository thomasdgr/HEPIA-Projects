
public class Equal extends Relation {

    public Equal(String fl, int line, int col) {
        super(fl, line, col);
    }

    public String operator() {
        return "==";
    }

    @Override
    public String toString(){
        return " == ";
    }

    public int apply(int left, int right){
        return (left == right) ? 1 : 0;
    }
    
    public boolean apply(boolean left, boolean right){
        return left == right;
    }
    
    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
