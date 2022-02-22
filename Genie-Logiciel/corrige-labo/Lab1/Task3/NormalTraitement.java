package dp;

public class NormalTraitement extends Traitement {

	public String traiteCalories(String nom) {
		String calories = CaloriesNormal.calculCalories(nom);
		return calories;
	}

}
