package dp;

public class Banane extends Fruit {

	Banane(Calories dp) {
		super(dp, "Banane", false);
	}

	public void notifier() {
		System.out.println("La notification a été reçu par Banane.");
	}

	public void notifier(String nom, Integer calories) {
		System.out.println("La notification a été reçu par Banane: " + nom + " à changé: " + calories + " calories");
	}

}