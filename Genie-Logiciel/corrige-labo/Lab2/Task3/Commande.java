package dp;

public class Commande {

	private EtatCommande etatCommande;

	private static Commande commande = null;
	private Fruit[] panier = new Fruit[5];

	private int compteur;

	public Commande() {
		super();
		etatCommande = new EnAttente(); // Etat initial
	}

	public static abstract class EtatCommande { // Transition d'état

		/**
		 * Méthode protégée permettant de changer l'état
		 * 
		 * @param cClasse
		 * @param cEtat
		 */
		protected void setEtat(Commande cClasse, EtatCommande cEtat) {
			cClasse.etatCommande = cEtat;
		}

		public abstract void payerCommande(Commande pClasse);

		public abstract void envoyerCommande(Commande pClasse);

		public abstract void annulerCommande(Commande pClasse);

		// Affichage de l'état courant
		public abstract String afficherEtat();

	}

	public void payerCommande() {
		etatCommande.payerCommande(this);
	}

	public void envoyerCommande() {
		etatCommande.envoyerCommande(this);
	}

	public void annulerCommande() {
		etatCommande.annulerCommande(this);
	}

	/**
	 * Affichage de l'état courant
	 */
	public String afficher() {
		return etatCommande.afficherEtat();
	}

	public void traiterCommande() {

		if (commande != null) {
			if (commande.afficher() == "Envoyée") {
				System.out.println("Votre commande a été envoyée");
				// System.out.println("Etat de la commande: " +
				// commande.afficher());
			}

			if (commande.afficher() == "Payée") {
				commande.envoyerCommande();
				System.out.println("Etat de la commande: " + commande.afficher());
			}

			if (commande.afficher() == "En attente") {
				System.out.println("Etat de la commande: " + commande.afficher());
				commande.payerCommande();
				System.out.println("Etat de la commande: " + commande.afficher());
			}
		} else {
			System.out.println("Commande vide!");
		}
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