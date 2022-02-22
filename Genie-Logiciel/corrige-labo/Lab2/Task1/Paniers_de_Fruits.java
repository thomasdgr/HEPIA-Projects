package dp;

import java.util.ArrayList;
import java.util.List;

public class Paniers_de_Fruits extends Fruit {

	public Paniers_de_Fruits(Calories dp, String nom, Boolean pepin) {
		super(dp, nom, pepin);
		// TODO Auto-generated constructor stub
	}

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
		if (getPepin()) {
			System.out.println("Panier a des pépins");
		} else {
			System.out.println("Panier n'a pas de pépin");
		}
	}

	public Boolean getPepin() {
		for (Fruit f : fruits) {
			if (f.getPepin()) {
				return true;
			}
		}
		return false;
	}

}
