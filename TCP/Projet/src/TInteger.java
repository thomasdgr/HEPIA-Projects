public class TInteger extends Expression{

    private String type;

    public TInteger( String fl, int line, int col){
        super(fl,line,col);
        this.type = "int";
    }

    public String getType() {
        return this.type;
    }

    @Override
    public String toString(){
        return "TInteger -> \n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
