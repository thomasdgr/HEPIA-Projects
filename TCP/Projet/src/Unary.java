public abstract class Unary extends Expression {
    protected Expression operande;

    public Unary(String fl, int line, int col) {
        super(fl, line, col);
    }

    public Expression getOperande() {
        return this.operande;
    }

    public abstract String operator();

    public void setOperande(Expression exp) {
        this.operande = exp;
    }

    @Override
    public String toString(){
        return "Unary -> operande : " + this.operande.toString() + "\n";
    }
}
