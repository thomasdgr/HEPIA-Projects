import java.util.*;

public class SourceCodeGenerator implements AbstracTreeVisitor{

    private String code = "";
    private int level = 0;

    private void addTabulation(){
        addTabulation(level);
    }

    private void addTabulation(int level){
        for (int i = 0; i < level; i++)
            code += "    ";
    }

    public Object visit(Addition node){
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(Assignment node){
        node.getDst().accept(this);
        code += " = ";
        node.getSrc().accept(this);
        code += ";";
        return null;
    }

    public Object visit(Block node){
        level+=1;
        for (Instruction inst: node.getInstructions()){
            code += "\n";
            addTabulation();
            inst.accept(this);
        }
        level-=1;
        return null;
    }

    public Object visit(Condition node){
        code += "si ";
        node.getCondition().accept(this);
        code += " alors";
        level += 1;
        for (Instruction inst: node.getThen()){
            code += "\n";
            addTabulation();
            inst.accept(this);
        }

        if (node.elseExist()){
            code += "\n";
            addTabulation(level - 1);
            code += "sinon";
            for (Instruction inst: node.getElse()){
                code += "\n";
                addTabulation();
                inst.accept(this);
            }
        }
        level -= 1;
        code += "\n";
        addTabulation();
        code += "finsi";
        return null;
    }

    public Object visit(DeclarConst node){
        code += "const " + node.getType().toString() + " " + node.getName() + " = ";
        node.getExpression().accept(this);
        code += ";";
        return null;
    }

    public Object visit(ProgramDeclaration node){
        level += 1;
        code += "programme ";
        node.getIdentifier().accept(this);
        node.getDeclaration().accept(this);
        code += "\ndebutprg";
        node.getInstructions().accept(this);
        code += "\nfinprg";
        level -= 1;
        return null;
    }

    public Object visit(DeclarVar node){
        code += node.getType().toString();
        code += " " ;
        for (Idf inst: node.getNames()){
            inst.accept(this);
            code += " ";
        }
        code += ";";
        return null;
    }

    public Object visit(Different node){
        node.getLeft().accept(this);
        code += node.operator() ;
        node.getRight().accept(this);
        return null;
    }

    public Object visit(Division node){
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(Write node){
      code += "ecrire ";
      if(node.getContent()!= null){
        code += node.getContent();
    } else {
       code += node.getExpression();
    }
      code += ";";
      return null;
    }

    public Object visit(Equal node){  
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(And node){
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(False node){
        code += "faux";
        return null;
    }
    public Object visit(Idf node){
        code += node.getName();
        return null;
    }

    public Object visit(InfEqual node){
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(Inferior node){
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(Read node){
        code += "lire ";
        node.getContent().accept(this);
        code += ";";
        return null;
    }

    public Object visit(Number node){
        code += Integer.toString(node.getValue());
        return node;
    }

    public Object visit(Not node){
        code += " " + node.operator() + " ";
        node.getOperande().accept(this);
        return null;
    }

    public Object visit(Or node){
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(Parenthesis node){
        code += "(";
        node.getOperande().accept(this);
        code += ")";
        return null;
    }

    public Object visit(For node){
        code += "pour ";
        node.getId().accept(this);
        code += " allant de ";
        node.getLowerTerm().accept(this);
        code += " a ";
        node.getUpperTerm().accept(this);
        code+= " faire";
        level += 1;
        for (Instruction inst: node.getInstructions()){
            code += "\n";
            addTabulation();
            inst.accept(this);
        }
        level -= 1;
        code += "\n";
        addTabulation();
        code += "fin-pour";
        return null;
    }

    public Object visit(Mult node){
        node.getLeft().accept(this);
        code += " * ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(SubUnary node){
        code += node.operator() + " ";;
        node.getOperande().accept(this);
        return null;
    }

    public Object visit(AddUnary node){
        code += node.operator() + " ";;
        node.getOperande().accept(this);
        return null;
    }

    public Object visit(Sub node){
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(SupEqual node){
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(Superior node){
        node.getLeft().accept(this);
        code += " " + node.operator() + " ";
        node.getRight().accept(this);
        return null;
    }

    public Object visit(While node){
        code += "tant-que ";
        node.getTerm().accept(this);
        code += " faire";
        level += 1;
        for (Instruction inst: node.getInstructions()){
            code += "\n";
            addTabulation();
            inst.accept(this);
        }
        level -= 1;
        code += "\n";
        addTabulation();
        code += "fintantque";
        return null;
    }

    public Object visit(Tilda node){
        code += "~ ";
        node.getOperande().accept(this);
        return null;
    }

    public Object visit(True node){
        code += "vrai";
        return null;
    }

    public String getCode(){
        return code;
    }
}
