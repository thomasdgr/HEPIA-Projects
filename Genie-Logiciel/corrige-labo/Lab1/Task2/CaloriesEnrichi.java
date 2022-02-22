package dp;

public class CaloriesEnrichi {

	private static String calories;
	private static String[][] tableau_fruit_calories = { { "Banane", "Kiwi", "Mangue", "Pomme" }, // tableau
			// [0]
			// de
			// String
			{ "109", "81", "117", "72" } // tableau [1] de String
	};

	static public void calculCalories(String nom) {
		// TODO Auto-generated method stub
		System.out.println("Calorie Enrichi: " + nom);

		int i;
		for (i = 0; i < tableau_fruit_calories[0].length; i++) {
			if (tableau_fruit_calories[0][i].equals(nom)) {
				calories = tableau_fruit_calories[1][i];
				break;
			}
		}
		System.out.println("Resultat: " + nom + " a " + calories + " calories/100g");
	}
}
