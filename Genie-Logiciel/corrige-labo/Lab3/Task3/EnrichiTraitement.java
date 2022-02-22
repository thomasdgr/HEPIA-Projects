package dp;

public class EnrichiTraitement extends Calories {

	public int traiterCalories(String nom) {
		return CaloriesEnrichi.calculerCalories(nom);
	}

	public int changerCalories(String nom, Integer calories) {
		notifierObserveurs(nom, calories);
		return CaloriesEnrichi.changerCalories(nom, calories);
	}
}
