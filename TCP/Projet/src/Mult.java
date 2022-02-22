public class Mult extends Arithmetic {
    public Mult(String fl, int line, int col) {
        super(fl, line, col);
    }

    public String operator() {
        return "*";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }

    public int apply(int left, int right){
        return left * right;
    }

    public boolean apply(boolean left, boolean right){
        return ((left ? 1 : 0) * (right ? 1 : 0)) != 0;
    }
}
