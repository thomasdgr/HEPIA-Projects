package dp;

public class Client {

	public Client() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		Fruit f1, f2, f3, f4;
		Calories dp;
		dp = new CaloriePauvre();
		f1 = new Fruit(dp, "Banane", false);

		dp = new CalorieNormale();
		f2 = new Fruit(dp, "Kiwi", true);

		dp = new CalorieEnrichie();
		f3 = new Fruit(dp, "Mangue", false);

		// Ajout de calories très pauvres
		dp = new CalorieTresPauvre();
		f4 = new Fruit(dp, "Pomme", true);

		f1.afficherFruit();
		f2.afficherFruit();
		f3.afficherFruit();

		f4.afficherFruit();
	}

}
