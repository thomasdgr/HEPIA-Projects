package dp;

import java.time.LocalDateTime;

public final class Commande {

	private EtatCommande etatCommande;

	private static Commande commande = null;
	private Fruit[] panier = new Fruit[5];

	private int compteur;

	Commande() {
		super();
		etatCommande = new EnAttente(); // état initial
	}

	public void archiverCommande() {
		etatCommande.archiverCommande();
	}

	public void payerCommande() {
		etatCommande.payerCommande();
	}

	public void envoyerCommande() {
		etatCommande.envoyerCommande();
	}

	public void annulerCommande() {
		etatCommande.annulerCommande();
	}

	public String getStatus() {
		return etatCommande.getStatus();
	}

	public void traiterCommande() {

		if (commande != null) {

			if (etatCommande.getStatus() == "Archivée") {
				// System.out.println("La commande a bien été archivée à ");
			}

			if (etatCommande.getStatus() == "Envoyée") {
				System.out.println("La commande a bien été envoyée");
				commande.archiverCommande();
			}

			if (etatCommande.getStatus() == "Payée") {
				commande.envoyerCommande();
			}

			if (etatCommande.getStatus() == "En attente") {
				commande.payerCommande();
			}

		} else {
			System.out.println("Commande vide!");
		}

	}

	interface EtatCommande { // Transition d'état
		public void payerCommande();

		public void envoyerCommande();

		public void archiverCommande();

		public void annulerCommande();

		public String getStatus();

	}

	class EnAttente implements EtatCommande {

		@Override
		public void payerCommande() {
			etatCommande = new Payée();

		}

		@Override
		public void envoyerCommande() {
			System.out.println("Vous devez d'abord payer votre commande avant de pouvoir l'envoyer");

		}

		@Override
		public void archiverCommande() {
			System.out.println("Imposible, vous n'avez passé aucune commande");

		}

		@Override
		public void annulerCommande() {
			System.out.println("Imposible, vous n'avez passé aucune commande");

		}

		@Override
		public String getStatus() {
			return "En attente";

		}

	}

	class Payée implements EtatCommande {

		@Override
		public void payerCommande() {
			System.out.println("Vous avez déjà payé la commande");

		}

		@Override
		public void envoyerCommande() {
			System.out.println("Votre commande a été traitée");
			etatCommande = new Envoyée();

		}

		@Override
		public void archiverCommande() {
			System.out.println("Avant d'achiver la commande, il faut l'envoyer");

		}

		@Override
		public void annulerCommande() {
			System.out.println("Votre paiement a été annulé");
			etatCommande = new EnAttente();

		}

		@Override
		public String getStatus() {
			return "Payée";

		}

	}

	class Envoyée implements EtatCommande {

		@Override
		public void payerCommande() {
			System.out.println("Vous avez déjà payé la commande");

		}

		@Override
		public void envoyerCommande() {
			System.out.println("Votre commande a déjà été envoyée");
			// etatCommande = new EnAttente();

		}

		@Override
		public void archiverCommande() {
			// System.out.println("Archivage de votre commande");
			System.out.println("La commande a bien été archivée à " + LocalDateTime.now());

		}

		@Override
		public void annulerCommande() {
			System.out.println("Impossible d'annuler votre commande, paiement déjà effectué");

		}

		@Override
		public String getStatus() {
			return "Envoyée";

		}

	}

	class Archivée implements EtatCommande {

		@Override
		public void payerCommande() {
			System.out.println("Vous avez déjà payé la commande");

		}

		@Override
		public void envoyerCommande() {
			System.out.println("Votre commande a déjà été envoyée");
			// etatCommande = new EnAttente();

		}

		@Override
		public void archiverCommande() {
			System.out.println("Archivage de votre commande");

		}

		@Override
		public void annulerCommande() {
			System.out.println("Impossible d'annuler votre commande, paiement déjà effectué");

		}

		@Override
		public String getStatus() {
			return "Archivée";

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