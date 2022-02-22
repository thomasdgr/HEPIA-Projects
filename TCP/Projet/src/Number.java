public class Number extends Expression {
    private Integer value;

    public Number(Integer val, String fl, int line, int col) {
        super(fl, line, col);
        this.value = val;
    }

    public Integer getValue() {
        return this.value;
    }

    public String getName() {
        return "entier";
    }

    @Override
    public String toString(){
        return this.value.toString();
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
