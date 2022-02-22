package dp;

public class PauvreTraitement extends Traitement {

	public String traiteCalories(String nom) {
		String calories = CaloriesPauvre.calculCalories(nom);
		return calories;
	}

}
