package dp;

public class CalorieTresPauvre extends Calories {

	public int traiterCalories(String nom) {
		return TraitementTresPauvre.calculerCalories(nom);
	}

}
