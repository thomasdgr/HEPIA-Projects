public abstract class Relation extends Binary {
    public Relation(String fl, int line, int col) {
        super(fl, line, col);
    }

    @Override
    public String toString(){
        return "Relation -> \n";
    }
}
