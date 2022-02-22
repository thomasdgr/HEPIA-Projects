public class False extends Expression {
    private boolean state;

    public False(String fl, int line, int col) {
        super(fl, line, col);
        this.state = false;
    }

    public boolean getState() {
        return this.state;
    }

    public String getName() {
        return "booleen";
    }

    @Override
    public String toString(){
        return "False -> " + Boolean.toString(state) + "\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}