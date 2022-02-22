import java.util.*;

public class SemanticAnalyzer implements AbstracTreeVisitor{
    private HashMap<String, Symbole> TDS = new HashMap<>();

    SemanticAnalyzer(HashMap<String, Symbole> newTDS){
        this.TDS = newTDS;
    }

    // en fonction de la Class d'un noeud, on determine si son type est "entier" ou "booleen"
    public String checkIfTypeIsIntegerOrBoolean(Object node){
        // on regarde toujours sur les types les plus bas possible (pas d'addition, de soustraction, de egal ...)
        switch (node.getClass().getName()) {
            case "Number":
                return "entier";
            case "AddUnary":
                return "entier";
            case "Tilda":
                return "entier";
            case "Not":
                return "booleen";
            case "SubUnary":
                return "entier";
            case "True":
                return "booleen";
            case "False":
                return "booleen";
            case "Idf":
                // si c'est un idf on regarde son type dans la TDS
                String o = ((Idf)node).getName();
                if(TDS.containsKey(o)){
                    return TDS.get(o).getType();
                } else {
                    throw new RuntimeException("Undefined variable \"" + TDS.get(o).getName() + "\"");
                }
            default:
                return "error";
        }
    }

    // Pour un expression binaire donnée, on vérifie que les 2 expressions de droite et gauche soient de types égaux
    public Object checkIfTypesAreEquals(Binary node){
        // si ce sont des parenthèses, on va chercher le type de l'expression qui est contenu dans la parenthèsee
        if(node.getLeft().getClass().getName().equals("Parenthesis")){
            checkIfTypeIsIntegerOrBoolean(((Parenthesis)node.getLeft()).getOperande().accept(this));
            return node;
        }
        if(node.getRight().getClass().getName().equals("Parenthesis")){
            checkIfTypeIsIntegerOrBoolean(((Parenthesis)node.getRight()).getOperande().accept(this));
            return node;
        }
        String type1 = checkIfTypeIsIntegerOrBoolean(node.getLeft().accept(this));
        String type2 = checkIfTypeIsIntegerOrBoolean(node.getRight().accept(this));
        // Si les types sont les mêmes, on continue l'analyse sinon on plante
        if(type1.equals(type2)){
            return node;
        }
        throw new RuntimeException("opperation on different types is not allowed");
    }

    public Object visit(Addition node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(Assignment node){
        String o1 = ((Idf)node.getDst().accept(this)).getName();
        String type = "";
        // pour connaitre le type d'une expression, on prend constament l'expression de gauche 
        // jusqu'a tomber sur un type le plus bas possible (idf, number...)
        if(node.getSrc().accept(this) instanceof Binary){
            Object obj = (Binary)node.getSrc().accept(this);
            type = checkIfTypeIsIntegerOrBoolean(((Binary)obj).getLeft().accept(this));
            while(type.equals("error")){
                obj = ((Binary)obj).getLeft().accept(this);
                type = checkIfTypeIsIntegerOrBoolean(obj);
            }
        } else{
            type = checkIfTypeIsIntegerOrBoolean(node.getSrc().accept(this));
        }
        if(TDS.containsKey(o1)){
            if(TDS.get(o1).getIsConstant() == false){
                if(type.equals(TDS.get(o1).getType())){
                    return node;
                }
                throw new RuntimeException("Type of \"" + TDS.get(o1).getName() + "\" is not compatible with its assigment");
            }
            throw new RuntimeException("\"" + TDS.get(o1).getName() + "\" is a constant variable wich is impossible to change");
        }
        throw new RuntimeException("Undefined variable \"" + o1 + "\"");
    }

    public Object visit(Block node){
        for (Instruction inst: node.getInstructions()){
            inst.accept(this);
        }
        return node;
    }

    public Object visit(Condition node){
        node.getCondition().accept(this);
        for (Instruction inst: node.getThen()){
            inst.accept(this);
        }

        if (node.elseExist()){
            for (Instruction inst: node.getElse()){
                inst.accept(this);
            }
        }
        return node;
    }

    public Object visit(DeclarConst node){
        node.getExpression().accept(this);
        return node;
    }

    public Object visit(ProgramDeclaration node){
        node.getIdentifier().accept(this);
        node.getDeclaration().accept(this);
        node.getInstructions().accept(this);
        return node;
    }

    public Object visit(DeclarVar node){
        for (Idf inst: node.getNames()){
            inst.accept(this);
        }
        return node;
    }

    public Object visit(Different node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(Division node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(Write node){
        if(node.getContent()!= null){
            node.getContent();
        } else {
           node.getExpression().accept(this);
        }
        return node;
    }

    public Object visit(Equal node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(And node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(False node){
        return node;
    }
    public Object visit(Idf node){
        return node;
    }

    public Object visit(InfEqual node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(Inferior node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(Read node){
        node.getContent().accept(this);
        return node;
    }

    public Object visit(Number node){
        return node;
    }

    public Object visit(Not node){
        if(node.getOperande() instanceof Relation || checkIfTypeIsIntegerOrBoolean(node.getOperande()).equals("booleen")){
            node.getOperande().accept(this);
        } else {
            throw new RuntimeException("Not operation must be on boolean value");
        }
        return node;
    }

    public Object visit(Or node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(Parenthesis node){
        return node.getOperande();
    }

    public Object visit(For node){
        node.getId().accept(this);
        if(checkIfTypeIsIntegerOrBoolean(node.getId().accept(this)).equals("entier")){
            node.getLowerTerm().accept(this);
            node.getUpperTerm().accept(this);
            for (Instruction inst: node.getInstructions()){
                inst.accept(this);
            }
            return node;
        } else {
            throw new RuntimeException("Variable in for-loop must be integer");
        }
    }

    public Object visit(Mult node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(SubUnary node){
        if(node.getOperande().accept(this) instanceof Expression){
            node.getOperande().accept(this);
        } else {
            throw new RuntimeException("Unary operation must be on integer value");
        }
        return node.getOperande();
    }

    public Object visit(AddUnary node){
        if(node.getOperande().accept(this) instanceof Expression){
            node.getOperande().accept(this);
        } else {
            throw new RuntimeException("Unary operation must be on integer value");
        }
        return node;
    }

    public Object visit(Sub node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(SupEqual node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(Superior node){
        return checkIfTypesAreEquals((Binary)node);
    }

    public Object visit(While node){
        node.getTerm().accept(this);
        for (Instruction inst: node.getInstructions()){
            inst.accept(this);
        }
        return node;
    }

    public Object visit(Tilda node){
        if(checkIfTypeIsIntegerOrBoolean(node.getOperande().accept(this)).equals("entier")){
            node.getOperande().accept(this);
        } else {
            throw new RuntimeException("Unary operation must be on integer value");
        }
        return node;
    }

    public Object visit(True node){
        return node;
    }
}
