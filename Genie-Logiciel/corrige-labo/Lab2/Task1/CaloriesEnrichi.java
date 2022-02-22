package dp;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class CaloriesEnrichi {

	private static int calories;
	private static final Map<String, Integer> map_fruit_calories;
	static {
		map_fruit_calories = new HashMap<String, Integer>();
		map_fruit_calories.put("Banane", 109);
		map_fruit_calories.put("Kiwi", 81);
		map_fruit_calories.put("Mangue", 117);
		map_fruit_calories.put("Pomme", 72);
		map_fruit_calories.put("Pastèque", 80);
		map_fruit_calories.put("Orange", 97);
		map_fruit_calories.put("Poire", 117);
	}

	static public int calculerCalories(String nom) {
		// System.out.println("Calorie Enrichi: " + nom);

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
