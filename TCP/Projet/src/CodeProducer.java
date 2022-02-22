import java.util.*;

public class CodeProducer implements AbstracTreeVisitor{
    private static String cible = "";
    private static int index = 0;
    private List<String> lst = new ArrayList<>();
    private HashMap<String, Symbole> TDS = new HashMap<>();

    public CodeProducer(HashMap<String, Symbole> newTDS){
        this.TDS = newTDS;
    }

    public String cible(){
        return cible;
    }

    public Object visit(Addition node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        cible += "\niadd";
        return null;
    }              

    public Object visit(Assignment node){
        if(node.getSrc() instanceof AddUnary){
            node.getDst().accept(this);
        }
        node.getSrc().accept(this); 
        String name = ((Idf)node.getDst()).getName();
        cible += "\nistore " + lst.indexOf(name);
        return null;
    }

    public Object visit(Block node){
        for (Instruction inst: node.getInstructions()){
            inst.accept(this);
        }
        return null;
    }

    public Object visit(Condition node){
        node.getCondition().accept(this);
        int tmp = index;
        cible += "\nifeq label_" +  tmp;
        index++;
        int tmp2 = index;
        index++;
        for (Instruction inst: node.getThen()){
            inst.accept(this);
        }
        cible += "\ngoto label_" + tmp2 ;
        cible += "\nlabel_" + tmp + ":";
        if (node.elseExist()){
            for (Instruction inst: node.getElse()){
                inst.accept(this);
            }
        }
        cible += "\nlabel_" + tmp2 + ":";
        return null;
    }

    public Object visit(DeclarConst node){
        lst.add(node.getName().getName());
        cible += "\n.var " + index + " is ";
        cible += node.getName().getName();
        if(node.getType().equals("entier")){
            cible += " I";
        } else {
            cible += " Z";
        }
        node.getExpression().accept(this);
        cible += "\nistore " + lst.indexOf(node.getName().getName());
        index++;
        return null;
    }

    public Object visit(ProgramDeclaration node){
        cible += ".class public ";
        cible += node.getIdentifier().getName();
        cible += "\n.super java/lang/Object";
        cible += "\n.method public static main([Ljava/lang/String;)V";
        cible += "\n.limit stack 20000";
        cible += "\n.limit locals 200";
        node.getDeclaration().accept(this);
        node.getInstructions().accept(this);
        cible += "\nreturn";
        cible += "\n.end method";
        return null;
    }
    
    public Object visit(DeclarVar node){
        for (Idf inst: node.getNames()){
            lst.add(inst.getName());
            cible += "\n.var " + index + " is ";
            cible += inst.getName();
            if(node.getType().equals("entier")){
                cible += " I";
            } else {
                cible += " Z";
            }
            index++;
        }
        return null;
    }

    public Object visit(Different node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        int tmp = index;
        cible += "\nif_icmpne label_" +  tmp;
        index++;
        cible += "\nldc 0";
        int tmp2 = index;
        cible += "\ngoto label_" + tmp2 ;
        index++;
        cible += "\nlabel_" + tmp + ":";
        cible += "\nldc 1";
        cible += "\nlabel_" + tmp2 + ":";
        return null;
    }

    public Object visit(Division node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        cible += "\nidiv";
        return null;
    }

    public Object visit(Write node){
        if(node.getContent()!= null){
            cible += "\ngetstatic java/lang/System/out Ljava/io/PrintStream;";
            cible += "\nldc " + node.getContent();
            cible += "\ninvokevirtual java/io/PrintStream/print(Ljava/lang/String;)V";

        } else {
            node.getExpression().accept(this);
            cible += "\ngetstatic java/lang/System/out Ljava/io/PrintStream;";
            cible += "\nswap";
            cible += "\ninvokevirtual java/io/PrintStream/print(I)V";
        }
        return null;
    }

    public Object visit(Equal node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        int tmp = index;
        cible += "\nif_icmpeq label_" +  tmp;
        index++;
        cible += "\nldc 0";
        int tmp2 = index;
        cible += "\ngoto label_" + tmp2 ;
        index++;
        cible += "\nlabel_" + tmp + ":";
        cible += "\nldc 1";
        cible += "\nlabel_" + tmp2 + ":";
        return null;
    }

    public Object visit(And node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        cible += "\niand";
        return null;
    }

    public Object visit(False node){
        cible += "\nldc 0";
        return null;
    }
    public Object visit(Idf node){
        cible += "\niload " + lst.indexOf(node.getName());
        return null;
    }

    public Object visit(InfEqual node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        int tmp = index;
        cible += "\nif_icmple label_" +  tmp;
        index++;
        cible += "\nldc 0";
        int tmp2 = index;
        cible += "\ngoto label_" + tmp2 ;
        index++;
        cible += "\nlabel_" + tmp + ":";
        cible += "\nldc 1";
        cible += "\nlabel_" + tmp2 + ":";
        return null;
    }

    public Object visit(Inferior node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        int tmp = index;
        cible += "\nif_icmplt label_" +  tmp;
        index++;
        cible += "\nldc 0";
        int tmp2 = index;
        cible += "\ngoto label_" + tmp2 ;
        index++;
        cible += "\nlabel_" + tmp + ":";
        cible += "\nldc 1";
        cible += "\nlabel_" + tmp2 + ":";
        return null;
    }

    public Object visit(Read node){
        cible += "\nnew java/util/Scanner";
        cible += "\ndup";
        cible += "\ngetstatic java/lang/System/in Ljava/io/InputStream;";
        cible += "\ninvokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V";
        cible += "\ninvokevirtual java/util/Scanner/nextInt()I";
        cible += "\nistore " + lst.indexOf(node.getContent().getName());
        return null;
    }

    public Object visit(Number node){
        cible += "\nldc " + node.getValue();
        return null;
    }

    public Object visit(Not node){
        node.getOperande().accept(this);
        int tmp = index;
        cible += "\nifeq label_" +  tmp;
        cible += "\nldc 0";
        index++;
        int tmp2 = index;
        cible += "\ngoto label_" + tmp2 ;
        index++;
        cible += "\nlabel_" + tmp + ":";
        cible += "\nldc 1";
        cible += "\nlabel_" + tmp2 + ":";
        return null;

    }

    public Object visit(Or node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        cible += "\nior";
        return null;
    }

    public Object visit(Parenthesis node){
        node.getOperande().accept(this);
        return node.getOperande();
    }

    public Object visit(For node){
        node.getLowerTerm().accept(this);
        cible += "\nistore " + lst.indexOf(node.getId().getName());
        int tmp = index;
        index++;
        cible += "\nlabel_" + tmp + ":";
        node.getUpperTerm().accept(this);
        cible += "\niload " + lst.indexOf(node.getId().getName());
        int tmp2 = index;
        index++;
        cible += "\nif_icmplt label_" + tmp2;
        for (Instruction inst: node.getInstructions()){
            inst.accept(this);
        }
        cible += "\niload " + lst.indexOf(node.getId().getName());
        cible += "\nldc 1";
        cible += "\niadd";
        cible += "\nistore " + lst.indexOf(node.getId().getName());
        cible += "\ngoto label_" + tmp;
        cible += "\nlabel_" + tmp2 + ":";
        return null;
    }

    public Object visit(Mult node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        cible += "\nimul";
        return null;
    }

    public Object visit(SubUnary node){
        node.getOperande().accept(this);
        cible += "\nineg";
        return null;
    }

    public Object visit(AddUnary node){
        node.getOperande().accept(this);
        cible += "\niadd";
        return null;
    }

    public Object visit(Sub node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        cible += "\nisub";
        return null;
    }

    public Object visit(SupEqual node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        int tmp = index;
        cible += "\nif_icmpge label_" +  tmp;
        index++;
        cible += "\nldc 0";
        int tmp2 = index;
        cible += "\ngoto label_" + tmp2 ;
        index++;
        cible += "\nlabel_" + tmp + ":";
        cible += "\nldc 1";
        cible += "\nlabel_" + tmp2 + ":";
        return null;
    }

    public Object visit(Superior node){
        node.getLeft().accept(this);
        node.getRight().accept(this);
        int tmp = index;
        cible += "\nif_icmpgt label_" +  tmp;
        index++;
        cible += "\nldc 0";
        int tmp2 = index;
        cible += "\ngoto label_" + tmp2 ;
        index++;
        cible += "\nlabel_" + tmp + ":";
        cible += "\nldc 1";
        cible += "\nlabel_" + tmp2 + ":";
        return null;
    }

    public Object visit(While node){
        int tmp = index;
        index++;
        cible += "\nlabel_" + tmp + ":";
        node.getTerm().accept(this);

        int tmp2 = index;
        index++;
        cible += "\nifeq label_" +  tmp2;
        for (Instruction inst: node.getInstructions()){
            inst.accept(this);
        }
        cible += "\ngoto label_" + tmp;
        cible += "\nlabel_" + tmp2 + ":";
        return null;
    }

    public Object visit(Tilda node){
        cible += "\nldc 1 \nineg";
        node.getOperande().accept(this);
        cible += "\nixor";
        return null;
    }

    public Object visit(True node){
        cible += "\nldc 1";
        return null;
    }
}