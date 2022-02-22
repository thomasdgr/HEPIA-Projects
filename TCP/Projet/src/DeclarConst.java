public class DeclarConst extends Instruction {

    private String keyWordConst;
    private String type;
    private Idf name;
    private Expression expression;

    public DeclarConst(String s, String t, Idf n, Expression e, String fl, int line, int col){
        super(fl, line, col);
        this.keyWordConst = s;
        this.type = t;
        this.name = n;
        this.expression = e;
    }

    public Expression getExpression() {
        return this.expression;
    }

    public void setExpression(Expression e) {
        this.expression = e;
    }

    public Idf getName() {
        return this.name;
    }

    public void setName(Idf id) {
        this.name = id;
    }

    public String getType() {
        return this.type;
    }

    public void setType(String str) {
        this.type = str;
    }

    @Override
    public String toString(){
        return "DeclarConst ->\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }    
}
