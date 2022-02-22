public class AddUnary extends Unary {
    public AddUnary(String fl, int line, int col) {
        super(fl, line, col);
    }

    public String operator() {
        return "+";
    }

    @Override
    public String toString(){
        return "++";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
