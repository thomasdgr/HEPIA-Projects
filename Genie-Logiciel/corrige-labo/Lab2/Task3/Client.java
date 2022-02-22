package dp;

public class Client {

	public Client() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		Commande commande = new Commande();
		Fruit f1;
		Calories dp;

		dp = new PauvreTraitement();
		f1 = new Fruit(dp, "Banane", false);

		commande = Commande.getInstance();
		commande.ajouter(f1);

		System.out.println("---- 1er appel traiterCommande ----");
		commande.traiterCommande();
		System.out.println("---- 2e appel traiterCommande ----");
		commande.traiterCommande();
		System.out.println("---- 3e appel traiterCommande ----");
		commande.traiterCommande();
	}

}
