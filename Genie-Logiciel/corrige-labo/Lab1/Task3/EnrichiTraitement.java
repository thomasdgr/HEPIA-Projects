package dp;

public class EnrichiTraitement extends Traitement {

	public String traiteCalories(String nom) {
		String calories = CaloriesEnrichi.calculCalories(nom);
		return calories;
	}

}
