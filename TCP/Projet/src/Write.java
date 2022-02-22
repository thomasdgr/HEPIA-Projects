public class Write extends Instruction {
    
    private Expression expression;
    private String content;

    public Write(Expression e, String fl, int line, int col){
        super(fl, line, col);
        this.expression = e;
    }

    public Write(String str, String fl, int line, int col){
        super(fl, line, col);
        this.content = str;
    }

    public Expression getExpression() {
        return this.expression;
    }

    public void setExpression(Expression e) {
        this.expression = e;
    }

    public String getContent() {
        return this.content;
    }

    public void setContent(String str) {
        this.content = str;
    }

    @Override
    public String toString(){
        return "Write -> \n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}