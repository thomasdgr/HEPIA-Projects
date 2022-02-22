public class TBoolean extends Expression{

    private String type;

    public TBoolean( String fl, int line, int col){
        super(fl,line,col);
        this.type = "boolean";
    }

    public String getType() {
        return this.type;
    }

    @Override
    public String toString(){
        return "TBoolean ->\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
