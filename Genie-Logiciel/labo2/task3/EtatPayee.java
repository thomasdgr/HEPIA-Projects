public class EtatPayee implements EtatCommande{
    private static EtatPayee etatSingleton;

    static{
		etatSingleton = new EtatPayee();
	}

    public EtatPayee(){}

    public static EtatCommande getCurrentState(){
        return etatSingleton;
    }

    public void TraiterCommande(Commande maCommande){
        System.out.println("La commande a été traité");
        maCommande.SetCommandeState(EtatEnvoye.getCurrentState());
    }
} 