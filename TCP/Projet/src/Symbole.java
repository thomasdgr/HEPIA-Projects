public class Symbole {
    private String name;
    private String value;
    private String type;
    private boolean isConstant;
    
    public Symbole(String n, String v, String t, boolean c){
        setName(n);
        setValue(v);
        setType(t);
        setIsConstant(c);
    }

    public String getName(){
        return this.name;
    }

    public String getValue(){
        return this.value;
    }

    public String getType(){
        return this.type;
    }

    public boolean getIsConstant(){
        return this.isConstant;
    }

    public void setName(String n){
        this.name = n;
    }

    public void setValue(String v){
        this.value = v;
    }

    public void setType(String t){
        this.type = t;
    }

    public void setIsConstant(boolean c){
        this.isConstant = c;
    }

    @Override
    public String toString(){
        return this.type + " " + this.name + " = " + this.value + "; " + this.isConstant;
    }
}
