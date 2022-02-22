package calories;

import fruits.Fruit;
import java.util.ArrayList;
import java.util.List;

public abstract class Calories{

	private static List<Fruit> lstObserver = new ArrayList<>();

	public int getCalories(String nom){
		return 0;
	}

	public void setCalories(String nom, Integer value){}

	public static void addObserver(Fruit f){
		lstObserver.add(f);
	}

	public static void removeObserver(Fruit f){
		lstObserver.remove(f);
	}

	public void sendNotificationObserveurs(String nom, Integer value){
		for (Fruit f : lstObserver){
			f.sendNotification(nom, value);
		}
	}
}