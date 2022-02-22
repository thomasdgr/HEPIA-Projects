package dp;

public class EnAttente extends Commande.EtatCommande {

	public void payerCommande(Commande cClasse) {
		setEtat(cClasse, new Payée());
	}

	public void envoyerCommande(Commande pClasse) {
		System.out.println("Vous devez d'abord payer votre commande avant de pouvoir l'envoyer");
	}

	public void annulerCommande(Commande pClasse) {
		System.out.println("Imposible, vous n'avez passé aucune commande");
	}

	@Override
	public String afficherEtat() {
		return "En attente";
	}
}