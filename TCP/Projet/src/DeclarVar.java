import java.util.ArrayList;

public class DeclarVar extends Instruction{
    
    private String type;
    private ArrayList<Idf> name = null;

    public DeclarVar(String t, ArrayList<Idf> n, String fl, int line, int col){
        super(fl, line, col);
        this.type = t;
        this.name = n;
    }

    public String getType() {
        return this.type;
    }

    public void setType(String str) {
        this.type = str;
    }

    public ArrayList<Idf> getNames() {
        return this.name;
    }

    public void setName(ArrayList<Idf> names) {
        this.name = names;
    }

    @Override
    public String toString(){
        return "DeclarVar ->\n";
    }

    Object accept(AbstracTreeVisitor visitor){
        return visitor.visit(this);
    }
}
