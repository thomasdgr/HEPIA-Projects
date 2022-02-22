package dp;

public class Commande {

	private static final Commande singleton;
	private int compteur;
	private static String[][] panier;

	public static String[][] getPanier() {
		return panier;
	}

	public static void setPanier(String[][] panier) {
		Commande.panier = panier;
	}

	static {
		singleton = new Commande();
	}

	private Commande() {
		System.out.println("Instanciation du singleton");
		panier = new String[4][5];
	}

	public static Commande getInstance() {
		return singleton;
	}

	public void ajouter(Fruit f) {
		synchronized (this) {
			++compteur;
		}
		if (compteur <= 5) {
			System.out.println("........Fruit " + f.getNom() + " est ajouté à la commande");
			System.out.println(".." + compteur + " fruits dans le panier");
			panier[0][compteur - 1] = f.getNom();
			panier[1][compteur - 1] = Boolean.toString(f.getPepin());
			panier[2][compteur - 1] = f.get_calories_type();
			panier[3][compteur - 1] = f.AfficherCalories();

			if (compteur == 5) {
				afficherCommande();
			}
		}
	}

	public void afficherCommande() {
		String[][] panier = Commande.getPanier();
		System.out.println("");
		System.out.println("***********************************************");
		System.out.println("Mon panier: \n");

		for (int i = 0; i < 5; i++) {
			String nom = panier[0][i];
			String pepin = panier[1][i];
			String calories_type = panier[2][i];
			String calories = panier[3][i];
			System.out.println(nom + ": pepin = " + pepin + ", calories (" + calories_type + "): " + calories + "\n");

		}
		System.out.println("***********************************************");
		System.out.println("Fin du traitement, la panier est plein ! (nbre de fruit " + "= " + compteur + ")");
	}

}