package traitement;

import calories.Calories;
import calories.CaloriesPauvre;

public class PauvreTraitement extends Calories{

	public int getCalories(String n){
		return CaloriesPauvre.getCalories(n);
	}

	public void setCalories(String n, Integer value){
		sendNotificationObserveurs(n, value);
		CaloriesPauvre.setCalories(n, value);
	}
}
