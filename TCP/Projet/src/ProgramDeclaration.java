import java_cup.runtime.*;
import java.io.*;
import java.util.*;

public class ProgramDeclaration extends Instruction {

    protected Idf identifier;
    protected Block declarations;
    protected Block instructions;
    protected HashMap<String, Symbole> TDS = new HashMap<>();

    public ProgramDeclaration(Idf identifier, String fl, int line, int col, HashMap<String, Symbole> newTDS){
        super(fl, line, col);
        this.identifier = identifier;
        this.TDS = newTDS;
    }

    @Override
    public String toString(){
        return "program name : " + this.identifier + "\nDeclaration : " + this.declarations + "\nInstructions : " + this.instructions + "\n";
    }

    public Idf getIdentifier() {
        return this.identifier;
    }

    public Block getDeclaration() {
        return this.declarations;
    }

    public Block getInstructions() {
        return this.instructions;
    }

    public void setIdentifier(Idf identifier) {
        this.identifier = identifier;
    }

    public HashMap<String, Symbole> getTDS() {
        return this.TDS;
    }

    public void setDeclarations(Block declarations) {
        this.declarations = declarations;
    }

    public void setInstructions(Block instructions) {
        this.instructions = instructions;
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
