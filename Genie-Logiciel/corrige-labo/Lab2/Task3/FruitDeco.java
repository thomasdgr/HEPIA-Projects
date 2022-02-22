package dp;

public abstract class FruitDeco extends Fruit {

	private Fruit fruit;

	public FruitDeco(Fruit fruit) {
		super();
		this.fruit = fruit;

	}

	public void afficherFruit() {
		this.fruit.afficherFruit();
	}

	public abstract void afficherFruit(String decorator);

}
