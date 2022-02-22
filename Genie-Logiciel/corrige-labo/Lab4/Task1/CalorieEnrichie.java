package dp;

public class CalorieEnrichie extends Calories {

	public int traiterCalories(String nom) {
		return TraitementEnrichi.calculerCalories(nom);
	}

}
