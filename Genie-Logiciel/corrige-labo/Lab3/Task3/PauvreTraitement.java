package dp;

public class PauvreTraitement extends Calories {

	public int traiterCalories(String nom) {
		return CaloriesPauvre.calculerCalories(nom);
	}

	public int changerCalories(String nom, Integer calories) {
		notifierObserveurs(nom, calories);
		return CaloriesPauvre.setCalories(nom, calories);
	}
}
