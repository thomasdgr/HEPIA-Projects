public class EtatEnvoye implements EtatCommande{
    private static EtatEnvoye etatSingleton;

    static{
		etatSingleton = new EtatEnvoye();
	}

    public EtatEnvoye(){}

    public static EtatCommande getCurrentState(){
        return etatSingleton;
    }

    public void TraiterCommande(Commande maCommande){
        System.out.println("La commande a été envoyé");
    }
} 