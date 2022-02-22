import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class While extends Instruction {
    private Expression term;
    private ArrayList<Instruction> instructions;

    public While(ArrayList<Instruction> instruction, Expression term, String fl, int line, int col) {
        super(fl, line, col);
        this.setTerm(term);
        this.setInstructions(instruction);
    }

    @Override
    public String toString(){
        return "While -> Term :" + this.term + "Instructions : " + this.instructions.toString() + "\n" ;
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

    public Expression getTerm() {
        return this.term;
    }

    public void setTerm(Expression exp) {
        this.term = exp;
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
