package dp;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class CaloriesNormal {

	private static int calories;
	private static final Map<String, Integer> map_fruit_calories;
	static {
		map_fruit_calories = new HashMap<String, Integer>();
		map_fruit_calories.put("Banane", 89);
		map_fruit_calories.put("Kiwi", 61);
		map_fruit_calories.put("Mangue", 97);
		map_fruit_calories.put("Pomme", 52);
		map_fruit_calories.put("Pastèque", 30);
		map_fruit_calories.put("Orange", 47);
		map_fruit_calories.put("Poire", 57);
	}

	static public int calculerCalories(String nom) {
		// System.out.println("Calorie Normal: " + nom);

		Set<String> cles = map_fruit_calories.keySet();
		Iterator<String> it = cles.iterator();
		while (it.hasNext()) {
			String cle = (String) it.next();
			if (cle == nom) {
				calories = (Integer) map_fruit_calories.get(cle);
				break;
			}
		}
		return calories;
	}
}
