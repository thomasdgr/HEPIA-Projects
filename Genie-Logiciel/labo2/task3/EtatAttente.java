public class EtatAttente implements EtatCommande{
    private static EtatAttente etatSingleton;

    static{
		etatSingleton = new EtatAttente();
	}

    public EtatAttente(){}

    public static EtatCommande getCurrentState(){
        return etatSingleton;
    }

    public void TraiterCommande(Commande maCommande){
        maCommande.SetCommandeState(EtatPayee.getCurrentState());
    }
} 