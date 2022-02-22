package dp;

public class Mangue extends Fruit {

	Mangue(Calories dp) {
		super(dp, "Mangue", false);
	}

	public void notifier(String nom, Integer calories) {
		System.out.println("La notification a été reçu par Mangue: " + nom + " à changé: " + calories + " calories");
	}

}