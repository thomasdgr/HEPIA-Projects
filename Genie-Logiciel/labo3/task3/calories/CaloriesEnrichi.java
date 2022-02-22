package calories;

import java.util.Arrays;

public class CaloriesEnrichi{

	private static String[][] array = { {"Banane", "Pomme", "Orange"},
									    {    "60",    "63",     "69"} };

	static public int getCalories(String nom){
		return Integer.parseInt(array[1][Arrays.asList(array[0]).indexOf(nom)]);
	}

	static public void setCalories(String nom, Integer caloriesN){
		array[1][Arrays.asList(array[0]).indexOf(nom)] = caloriesN.toString();
	}
}