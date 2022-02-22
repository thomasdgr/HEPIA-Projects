package dp;

public class CaloriePauvre extends Calories {

	public int traiterCalories(String nom) {
		return TraitementPauvre.calculerCalories(nom);
	}

}
