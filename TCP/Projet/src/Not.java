public class Not extends Unary {
    public Not(String fl, int line, int col) {
        super(fl, line, col);
    }

    public String operator() {
        return "non";
    }

    @Override
    public String toString(){
        return "Not -> !\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
