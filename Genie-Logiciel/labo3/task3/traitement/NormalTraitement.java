package traitement;

import calories.Calories;
import calories.CaloriesNormal;

public class NormalTraitement extends Calories{

	public int getCalories(String n){
		return CaloriesNormal.getCalories(n);
	}

	public void setCalories(String n, Integer value){
		sendNotificationObserveurs(n, value);
		CaloriesNormal.setCalories(n, value);
	}
}
