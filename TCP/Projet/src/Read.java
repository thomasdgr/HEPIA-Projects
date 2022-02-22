public class Read extends Instruction {

    private Idf content;

    public Read(Idf str, String fl, int line, int col){
        super(fl, line, col);
        this.content = str;
    }

    public Idf getContent() {
        return this.content;
    }

    public void setContent(Idf str) {
        this.content = str;
    }

    @Override
    public String toString(){
        return "Read -> " + this.content.toString();
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
