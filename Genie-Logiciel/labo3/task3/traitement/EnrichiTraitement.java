package traitement;

import calories.Calories;
import calories.CaloriesEnrichi;

public class EnrichiTraitement extends Calories{

	public int getCalories(String n){
		return CaloriesEnrichi.getCalories(n);
	}

	public void setCalories(String n, Integer value){
		sendNotificationObserveurs(n, value);
		CaloriesEnrichi.setCalories(n, value);
	}
}
