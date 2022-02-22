package dp;

public class Payée extends Commande.EtatCommande {

	@Override
	public void payerCommande(Commande cClasse) {
		System.out.println("Vous avez déjà payé la commande");

	}

	@Override
	public void envoyerCommande(Commande cClasse) {
		System.out.println("Votre commande a été traitée");
		setEtat(cClasse, new Envoyée());

	}

	@Override
	public void annulerCommande(Commande cClasse) {
		System.out.println("Votre paiement a été annulé");
		setEtat(cClasse, new EnAttente());

	}

	@Override
	public String afficherEtat() {
		return "Payée";
	}
}