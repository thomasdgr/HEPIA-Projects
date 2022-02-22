public class Tilda extends Unary {
    public Tilda(String fl, int line, int col) {
        super(fl, line, col);
    }

    public String operator() {
        return "~";
    }

    @Override
    public String toString(){
        return "Tilda -> ~\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
