import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Block extends Instruction {
    private ArrayList<Instruction> instructions = null;

    public Block(ArrayList<Instruction> instructions, String fl, int line, int col) {
        super(fl, line, col);
        this.setInstructions(instructions);
    }

    public Block(String fl, int line, int col) {
        this(new ArrayList<Instruction>(), fl, line, col);
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

    @Override
    public String toString(){
        String result = "";
        for(Instruction i : this.instructions){
            result = result + i.toString();
        }
        return "\n" + result + "\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
