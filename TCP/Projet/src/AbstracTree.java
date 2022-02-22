public abstract class AbstracTree {
    private String filename = "";
    private int line = -1;
    private int column = -1;

    public AbstracTree(String fl, int line, int col) {
        this.filename = fl;
        this.line = line;
        this.column = col;
    }

    public String getFilename() {
        return this.filename;
    }

    public int getLine() {
        return this.line;
    }

    public int getColumn() {
        return this.column;
    }

    @Override
    public String toString(){
        return "";
    }
    abstract Object accept(AbstracTreeVisitor visitor);
}
