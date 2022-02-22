public class And extends Arithmetic {
    public And(String fl, int line, int col) {
        super(fl, line, col);
    }

    public String operator() {
        return " et ";
    }

    @Override
    public String toString(){
        return " and ";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }

    public int apply(int left, int right){
        return left & right;
    }

    public boolean apply(boolean left, boolean right){
        return ((left ? 1 : 0) & (right ? 1 : 0)) != 0;
    }
}