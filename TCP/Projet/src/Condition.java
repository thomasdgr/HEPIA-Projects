import java.lang.Math;
import java.util.List;
import java.util.ArrayList;

public class Condition extends Instruction {
    private Expression condition;
    private ArrayList<Instruction> elseInstruction = null;
    private ArrayList<Instruction> thenInstruction = null;

    public Condition(ArrayList<Instruction> elseInstruction, ArrayList<Instruction> thenInstruction, Expression condition, String fl, int line, int col) {
        super(fl, line, col);
        this.setCondition(condition);
        this.setElse(elseInstruction);
        this.setThen(thenInstruction);
    }

    public Condition(ArrayList<Instruction> thenInstruction, Expression condition, String fl, int line, int col) {
        super(fl, line, col);
        this.setCondition(condition);
        this.setThen(thenInstruction);
    }

    public Expression getCondition() {
        return this.condition;
    }

    public ArrayList<Instruction> getElse() {
        return this.elseInstruction;
    }

    public ArrayList<Instruction> getThen() {
        return this.thenInstruction;
    }
    
    public void setCondition(Expression exp) {
        this.condition = exp;
    }

    public void setElse(ArrayList<Instruction> elseInstruction) {
        this.elseInstruction = elseInstruction;
    }

    public void setThen(ArrayList<Instruction> thenInstruction) {
        this.thenInstruction = thenInstruction;
    }

    public void addElse(Instruction instr) {
        this.elseInstruction.add(instr);
    }

    public void addThen(Instruction instr) {
        this.thenInstruction.add(instr);
    }

    public int sizeElse() {
        return this.elseInstruction.size();
    }

    public int sizeThen() {
        return this.thenInstruction.size();
    }

    public boolean elseExist(){
      return elseInstruction != null;
    }


    @Override
    public String toString(){
        String resultThen = "";
        for(Instruction i : this.thenInstruction){
            resultThen = resultThen + i.toString();
        }

        if(this.elseInstruction == null){

            return "Condition -> thenInstruction :\n" + this.thenInstruction.toString() + ", Expression : " + this.condition.toString();
        }
        String resultElse = "";
        for(Instruction i : this.elseInstruction){
            resultElse = resultElse + i.toString();
        }

        return "Condition -> thenInstruction :\n" + this.thenInstruction.toString() + "ElseInstruction :\n" + this.thenInstruction.toString() + ", Expression : " + this.condition.toString();
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
