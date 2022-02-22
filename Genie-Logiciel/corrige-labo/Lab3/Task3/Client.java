package dp;

public class Client {

	public Client() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		Fruit f1, f2, f3;
		Calories dp;
		dp = new PauvreTraitement();
		f1 = new Banane(dp);

		dp = new NormalTraitement();
		f2 = new Kiwi(dp);

		dp = new EnrichiTraitement();
		f3 = new Mangue(dp);

		// Ajouter les observeurs
		Calories.ajouterObserveur(f1);
		Calories.ajouterObserveur(f2);
		Calories.ajouterObserveur(f3);

		f2.afficherFruit();

		f2.changerCalories(58); // Changer les calories d'un fruit

		f2.afficherFruit();

		// Supprimer un observeur
		Calories.SupprimerObserveur(f3);

		f1.changerCalories(61); // Changer les calories d'un fruit

		f1.afficherFruit();
	}

}
