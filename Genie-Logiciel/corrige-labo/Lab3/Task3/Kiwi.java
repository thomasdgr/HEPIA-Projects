package dp;

public class Kiwi extends Fruit {

	Kiwi(Calories dp) {
		super(dp, "Kiwi", true);
	}

	public void notifier(String nom, Integer calories) {
		System.out.println("La notification a été reçu par Kiwi: " + nom + " à changé: " + calories + " calories");
	}
}