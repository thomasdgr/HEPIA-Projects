public class True extends Expression {
    private boolean state;

    public True(String fl, int line, int col) {
        super(fl, line, col);
        this.state = true;
    }

    public boolean getState() {
        return this.state;
    }

    public String getName() {
        return "booleen";
    }

    @Override
    public String toString(){
        return "True -> " + Boolean.toString(state) + "\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
