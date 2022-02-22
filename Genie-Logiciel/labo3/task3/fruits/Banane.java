package fruits;

import calories.Calories;

public class Banane extends Fruit{

	public Banane(Calories c){
		super(c, "Banane", false);
	}

	public void sendNotification(String nom, Integer value){
		System.out.println("Banane recoit une update -> " + nom + " avec " + value + " calories");
	}

}