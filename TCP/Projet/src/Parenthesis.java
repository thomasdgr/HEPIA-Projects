public class Parenthesis extends Expression {
    protected Expression operande;

    public Parenthesis(Expression e, String fl, int line, int col) {
        super(fl, line, col);
        setOperande(e);
    }

    public Expression getOperande() {
        return this.operande;
    }

    public void setOperande(Expression exp) {
        this.operande = exp;
    }

    @Override
    public String toString(){
        return "Parenthesis : " + this.operande.toString() + "\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
