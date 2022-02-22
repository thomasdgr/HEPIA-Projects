public class SubUnary extends Unary {
    public SubUnary(String fl, int line, int col) {
        super(fl, line, col);
    }

    public String operator() {
        return "-";
    }

    @Override
    public String toString(){
        return "SubUnary -> --\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}