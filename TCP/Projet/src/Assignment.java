public class Assignment extends Instruction {
    protected Expression source;
    protected Expression destination;

    public Assignment(Expression dest, Expression src, String fl, int line, int col) {
        super(fl, line, col);
        this.setSrc(src);
        this.setDst(dest);
    }

    public Expression getSrc() {
        return this.source;
    }

    public Expression getDst() {
        return this.destination;
    }

    public void setSrc(Expression exp) {
        this.source = exp;
    }

    public void setDst(Expression exp) {
        this.destination = exp;
    }

    @Override
    public String toString(){
        return destination  + " = " + source + "\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
