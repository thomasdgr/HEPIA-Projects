public abstract class Instruction extends AbstracTree {
    public Instruction(String fl, int line, int col) {
        super(fl, line, col);
    }

    @Override
    public String toString(){
        return "Instruction ->\n";
    }
}
