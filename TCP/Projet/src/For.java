import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class For extends Instruction {
    private Idf id;
    private Expression lowerTerm;
    private Expression upperTerm;
    private ArrayList<Instruction> instructions = null;

    public For(ArrayList<Instruction> inst, Idf idf, Expression lowerTerm, Expression upperTerm, String fl, int line, int col) {
        super(fl, line, col);
        this.id = idf;
        this.setLowerTerm(lowerTerm);
        this.setUpperTerm(upperTerm);
        this.setInstructions(inst);
    }

    @Override
    public String toString(){
        String instr = "";
        for(Instruction i : this.instructions){
            instr = instr + i.toString();
        }
        return "For -> " + "Idf : " + this.id.toString() + "Lower Term : " + lowerTerm.toString() + "Upper Term : " + upperTerm.toString() + "instructions : " + instr;

    }

    public ArrayList<Instruction> getInstructions() {
        return this.instructions;
    }

    public void setInstructions(ArrayList<Instruction> instructions) {
        this.instructions = instructions;
    }

    public void addInstruction(Instruction instr) {
        this.instructions.add(instr);
    }

    public int size() {
        return this.instructions.size();
    }

    public Expression getLowerTerm() {
        return this.lowerTerm;
    }

    public Expression getUpperTerm() {
        return this.upperTerm;
    }

    public void setLowerTerm(Expression exp) {
        this.lowerTerm = exp;
    }

    public void setUpperTerm(Expression exp) {
        this.upperTerm = exp;
    }

    public Idf getId() {
        return this.id;
    }

    public void setId(Idf i) {
        this.id = i;
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
