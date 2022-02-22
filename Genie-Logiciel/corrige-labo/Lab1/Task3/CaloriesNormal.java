package dp;

public class CaloriesNormal {

	private static String calories;
	private static String[][] tableau_fruit_calories = {
			{ "Banane", "Kiwi", "Mangue", "Pomme", "Pastèque", "Orange", "Poire" }, // tableau
			// [0]
			// de
			// String
			{ "89", "61", "97", "52", "30", "47", "57" } // tableau [1] de
															// String
	};

	static public String calculCalories(String nom) {
		// System.out.println("Calorie Normal: " + nom);

		int i;
		for (i = 0; i < tableau_fruit_calories[0].length; i++) {
			if (tableau_fruit_calories[0][i].equals(nom)) {
				calories = tableau_fruit_calories[1][i];
				break;
			}
		}
		// System.out.println("Resultat: " + nom + " a " + calories + "
		// calories/100g");
		return calories;
	}
}
