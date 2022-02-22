public class Commande{

    private static final Commande singleton;
    private static Fruit[] contenu; 
    
    static{
		singleton = new Commande();
	}
    
    private Commande(){
        Commande.contenu = new Fruit[5];
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

    public void AfficherCommande(){
        for(int i = 0; i < Commande.contenu.length; i++){
            Commande.contenu[i].AfficherCalories();
        }
    } 
} 