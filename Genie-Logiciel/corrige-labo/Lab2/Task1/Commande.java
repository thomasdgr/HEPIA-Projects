package dp;

public final class Commande {

	private static Commande commande = null;
	private Fruit[] panier = new Fruit[5];

	private int compteur;

	private Commande() {
		super();
	}

	public static Commande getInstance() {
		if (commande == null) {
			commande = new Commande();
			// System.out.println("Instanciation du singleton");
		}
		return commande;
	}

	public void setPanier(Fruit[] panier) {
		this.panier = panier;
	}

	public void ajouter(Fruit f) {

		if (compteur == 5) {
			System.out.println("Le panier est plein ! (nbre de fruit " + "= " + panier.length + ")");
		} else {
			// Ajouter fruit à un tableau de type Fruit
			compteur += 1;
			panier[compteur - 1] = f;
		}
	}

	public void afficherCommande() {
		for (int i = 0; i < compteur; i++) {
			panier[i].afficherFruit();
		}
	}
}