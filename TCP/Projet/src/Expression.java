public abstract class Expression extends AbstracTree {
    public Expression(String fl, int line, int col) {
        super(fl, line, col);
    }

    @Override
    public String toString(){
        return "exp";
    }
}
