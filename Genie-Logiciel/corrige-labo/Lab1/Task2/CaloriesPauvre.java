package dp;

public class CaloriesPauvre {

	private static String calories;
	private static String[][] tableau_fruit_calories = { { "Banane", "Kiwi", "Mangue", "Pomme" }, // tableau
			// [0]
			// de
			// String
			{ "29", "21", "57", "12" } // tableau [1] de String
	};

	static public void calculCalories(String nom) {
		// TODO Auto-generated method stub
		System.out.println("Calorie Pauvre: " + nom);

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
