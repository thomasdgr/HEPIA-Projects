public class Fruit{
    private String nom;
    private boolean pepin;

    public Fruit(){}

    public void setNom(String nom){
        this.nom = nom;
    }
    
    public void setPepin(boolean pepin){
        this.pepin = pepin;
    }
    
    public String getNom(){
        return this.nom;
    }
    
    public boolean getPepin(){
        return this.pepin;
    }
    
    public void AfficherFruit(){
        System.out.print("Le fruit \"" + getNom());
        System.out.println( (this.pepin) ? "\" contient des pépins" : "\" ne contient pas de pépins");
    }
}
