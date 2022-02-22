package dp;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class CaloriesPauvre {

	private static int calories;
	private static final Map<String, Integer> map_fruit_calories;
	static {
		map_fruit_calories = new HashMap<String, Integer>();
		map_fruit_calories.put("Banane", 29);
		map_fruit_calories.put("Kiwi", 21);
		map_fruit_calories.put("Mangue", 57);
		map_fruit_calories.put("Pomme", 12);
		map_fruit_calories.put("Pastèque", 10);
		map_fruit_calories.put("Orange", 15);
		map_fruit_calories.put("Poire", 20);
	}

	static public int calculerCalories(String nom) {
		// System.out.println("Calorie Pauvre: " + nom);

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
