package dp;

public class NormalTraitement extends Calories {

	public int traiterCalories(String nom) {
		return CaloriesNormal.calculerCalories(nom);
	}

	public int changerCalories(String nom, Integer calories) {
		notifierObserveurs(nom, calories); // v2.0
		return CaloriesNormal.changerCalories(nom, calories);
	}
}
