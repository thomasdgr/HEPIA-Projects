import java.util.*;

public abstract class Binary extends Expression {
    protected Expression operandeGauche;
    protected Expression operandeDroite;

    public Binary(String fl, int line, int col) {
        super(fl, line, col);
    }

    public Expression getLeft() {
        return this.operandeGauche;
    }

    public Expression getRight() {
        return this.operandeDroite;
    }

    public abstract String operator();

    public void setLeft(Expression exp) {
        this.operandeGauche = exp;
    }

    public void setRight(Expression exp) {
        this.operandeDroite = exp;
    }

    public abstract int apply(int left, int right);

    public abstract boolean apply(boolean left, boolean right);

    @Override 
    public String toString() {
        return this.operandeGauche + " " + this.operator() + " " + this.operandeDroite;
    }
}
    
