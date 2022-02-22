import java.util.*;

// pas de fonction visit pour les class qui ne sont pas des feuilles 
// dans l'Arbre Abstrait (donc pas de fonction accept non plus)

public interface AbstracTreeVisitor {
    Object visit(Addition node);
    Object visit(AddUnary node);
    Object visit(And node);
    //Object visit(Arithmetic node);
    Object visit(Assignment node);
    //Object visit(Binary node);
    Object visit(Block node);
    //Object visit(Chaine node);
    Object visit(Condition node);
    Object visit(DeclarConst node);
    Object visit(DeclarVar node);
    Object visit(Different node);
    Object visit(Division node);
    Object visit(Equal node);
    //Object visit(Expression node);
    Object visit(False node);
    Object visit(For node);
    Object visit(Idf node);
    //Object visit(Indice node);
    Object visit(InfEqual node);
    Object visit(Inferior node);
    //Object visit(Instruction node);
    Object visit(Mult node);
    Object visit(Not node);
    Object visit(Number node);
    Object visit(Or node);
    Object visit(Parenthesis node);
    Object visit(ProgramDeclaration node);
    Object visit(Read node);
    //Object visit(Relation node);
    Object visit(Sub node);
    Object visit(SubUnary node);
    Object visit(SupEqual node);
    Object visit(Superior node);
    //Object visit(Symbole node);
    Object visit(Tilda node);
    Object visit(True node);
    //Object visit(Unary node);
    Object visit(While node);
    Object visit(Write node);
}

















































































