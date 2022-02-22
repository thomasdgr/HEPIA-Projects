import fruits.Fruit;
import fruits.Banane;
import fruits.Orange;
import fruits.Pomme;

import calories.Calories;

import traitement.EnrichiTraitement;
import traitement.NormalTraitement;
import traitement.PauvreTraitement;

public class Client {
	public static void main(String[] args) {
		Calories c1 = new PauvreTraitement();
		Fruit f1 = new Banane(c1);

		Calories c2 = new NormalTraitement();
		Fruit f2 = new Orange(c2);

		Calories c3 = new EnrichiTraitement();
		Fruit f3 = new Pomme(c3);

		Calories.addObserver(f1);
		Calories.addObserver(f2);
		Calories.addObserver(f3);

		f1.afficherFruit();
		f1.setCalories(10);
		f1.afficherFruit();
		f2.afficherFruit();
		f3.afficherFruit();
		
		System.out.println();
		Calories.removeObserver(f3);

		f2.afficherFruit();
		f2.setCalories(20);
		f1.afficherFruit();
		f2.afficherFruit();
		f3.afficherFruit();
	}
}
