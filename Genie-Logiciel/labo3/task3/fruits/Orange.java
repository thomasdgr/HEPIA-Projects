package fruits;

import calories.Calories;

public class Orange extends Fruit{

	public Orange(Calories c){
		super(c, "Orange", true);
	}

	public void sendNotification(String nom, Integer value){
		System.out.println("Orange recoit une update -> " + nom + " avec " + value + " calories");
	}
}