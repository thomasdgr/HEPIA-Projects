package fruits;

import calories.Calories;

public class Pomme extends Fruit{

	public Pomme(Calories c){
		super(c, "Pomme", false);
	}

	public void sendNotification(String nom, Integer value){
		System.out.println("Pomme recoit un update -> " + nom + " avec " + value + " calories");
	}
}