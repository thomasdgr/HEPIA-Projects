public class Commande{
    
    private static final Commande singleton;
    private static Fruit[] contenu; 
    private EtatCommande etat;
    
    static{
		singleton = new Commande();
	}
    
    private Commande(){
        Commande.contenu = new Fruit[5];
        this.etat = EtatAttente.getCurrentState();
    }
    
    public Fruit[] getContent(){
        return Commande.contenu;
    }

    public void setContent(Fruit[] fruits){
        Commande.contenu = fruits;
    }

    public static Commande getInstance(){
        return singleton;
    }

    public void SetCommandeState(EtatCommande e){
        this.etat = e;
    }

    public void AfficherCommande(){
        for(int i = 0; i < Commande.contenu.length; i++){
            Commande.contenu[i].AfficherCalories();
        }
    }
    
    public void TraiterCommande(){
        this.etat.TraiterCommande(this);
    } 
} 

/*

if(this.etat instanceof EtatAttente){
    this.etat = new EtatPayee();
}
else if(this.etat instanceof EtatPayee){
    System.out.println("La commande a été traité");
    this.etat = new EtatEnvoye();
}
else if(this.etat instanceof EtatEnvoye){
    System.out.println("La commande a été envoyé");
}*/