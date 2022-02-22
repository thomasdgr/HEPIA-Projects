package dp;

public class Decoration extends FruitDeco {

	public Fruit fruit;

	public Decoration(Fruit fruit) {
		super(fruit); // ????
		this.fruit = fruit;
	}

	@Override
	public void afficherFruit(String decorator) {
		if ((decorator == "") | (decorator == "*") | (decorator == "#") | (decorator == "=") | (decorator == "&")) {
			System.out.println(getDeco(decorator));
			System.out.println();
			this.fruit.afficherFruit();
			System.out.println();
			System.out.println(getDeco(decorator));
		} else {
			System.out.println("Décoration inappropriée (" + decorator + ")");
		}
	}

	private String getDeco(String decorator) {
		String deco = "";
		for (int i = 0; i < 40; i++)
			deco += decorator;
		return deco;
	}
}
