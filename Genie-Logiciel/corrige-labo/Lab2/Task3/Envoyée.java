package dp;

public class Envoyée extends Commande.EtatCommande {

	@Override
	public void payerCommande(Commande pClasse) {
		System.out.println("Vous avez déjà payé la commande");

	}

	@Override
	public void envoyerCommande(Commande pClasse) {
		System.out.println("Votre commande a déjà été envoyée");
		// setEtat(pClasse, new EnAttente());
	}

	@Override
	public void annulerCommande(Commande pClasse) {
		System.out.println("Impossible d'annuler votre commande, paiement déjà effectué");

	}

	@Override
	public String afficherEtat() {
		return "Envoyée";
	}
}
