package dp;

import java.util.ArrayList;
import java.util.List;

public class Paniers_de_Fruits extends Fruit {

	private List<Fruit> fruits = new ArrayList<Fruit>();

	public void add(Fruit f) {
		// c.niveau = this.niveau + 1;
		fruits.add(f);
	}

	public void remove(Fruit f) {
		fruits.remove(f);

	}

	public List<Fruit> getChilds() {
		return fruits;
	}

	@Override
	public void afficherFruit() {
		// TODO Auto-generated method stub
		System.out.print("panier(");
		for (Fruit f : fruits) {
			System.out.print(f.getNom() + " ");
		}
		System.out.println(")");
	}

}
