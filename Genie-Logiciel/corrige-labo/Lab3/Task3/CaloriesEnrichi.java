package dp;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class CaloriesEnrichi {

	private static int calories;
	private static String etat_fruit;
	private static int etat_calories;

	private static final Map<String, Integer> map_fruit_calories;
	static {
		map_fruit_calories = new HashMap<String, Integer>();
		map_fruit_calories.put("Banane", 109);
		map_fruit_calories.put("Kiwi", 81);
		map_fruit_calories.put("Mangue", 117);
		map_fruit_calories.put("Pomme", 72);
	}

	static public int calculerCalories(String nom) {

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

	static public int changerCalories(String nom, Integer caloriesN) {
		Set<String> cles = map_fruit_calories.keySet();
		Iterator<String> it = cles.iterator();
		while (it.hasNext()) {
			String cle = (String) it.next();
			if (cle == nom) {
				map_fruit_calories.replace(cle, caloriesN);
				etat_fruit = cle; // 1er solution: tirré
				etat_calories = caloriesN; // 1er solution: tirré
				break;
			}
		}
		return caloriesN;
	}

	// 1er solution
	static public String getEtatFruit() {
		return etat_fruit;
	}

	// 1er solution
	static public int getEtatCalories() {
		return etat_calories;
	}
}
