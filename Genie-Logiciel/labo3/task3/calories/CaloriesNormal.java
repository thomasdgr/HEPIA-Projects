package calories;

import java.util.Arrays;

public class CaloriesNormal{

	private static String[][] array = { {"Banane", "Pomme", "Orange"},
									    {    "70",    "73",     "79"} };

	static public int getCalories(String nom){
		return Integer.parseInt(array[1][Arrays.asList(array[0]).indexOf(nom)]);
	}

	static public void setCalories(String nom, Integer caloriesN){
		array[1][Arrays.asList(array[0]).indexOf(nom)] = caloriesN.toString();
	}
}