package fruits;

import calories.Calories;

public abstract class Fruit{

	private String nom;
	private Boolean pepin;
	private Calories calories;

	Fruit(Calories c){
		this.calories = c;
	}

	public Fruit(Calories c, String n, Boolean p){
		this.nom = n;
		this.pepin = p;
		this.calories = c;
	}

	public String getNom(){
		return this.nom;
	}

	public void setNom(String n){
		this.nom = n;
	}

	public Boolean getPepin(){
		return this.pepin;
	}

	public void setPepin(Boolean p){
		this.pepin = p;
	}

	public int getCalories(){
		return this.calories.getCalories(this.getNom());
	}

	public void setCalories(Integer value){
		this.calories.setCalories(this.nom, value);
	}

	public void afficherFruit(){
        System.out.print("Le fruit \"" + this.getNom());
        System.out.print( this.getPepin() ? "\" contient des pépins" : "\" ne contient pas de pépins"); 
		System.out.println(" et possède " + this.getCalories() + " calories");
    }

	public void sendNotification(String nom, Integer calories){
		System.out.println("la notification a été envoyée");
	}
}
