package dp;

import java.util.ArrayList;
import java.util.List;

public abstract class Calories {

	private static List<Fruit> ListObserveurs = new ArrayList<>();

	public int traiterCalories(String nom) {
		return 0;
	}

	public int changerCalories(String nom, Integer calories) {
		return 0;
	}

	public static void ajouterObserveur(Fruit o) {
		ListObserveurs.add(o);

	}

	public static void SupprimerObserveur(Fruit o) {
		ListObserveurs.remove(o);

	}

	public void notifierObserveurs(String nom, Integer calories) {
		for (Fruit o : ListObserveurs)
			o.notifier(nom, calories);
	}
}