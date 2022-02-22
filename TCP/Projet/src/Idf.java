public class Idf extends Expression {
    private String name;

    public Idf(String name, String fl, int line, int col) {
        super(fl, line, col);
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    @Override
    public String toString(){
        return  this.name ;
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
