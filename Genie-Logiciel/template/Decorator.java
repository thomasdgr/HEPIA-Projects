public abstract class Decorator extends Fruit {
    private Fruit fruit;

	public Decorator(Fruit fruit){
		super(new CaloriesNormal());
		this.fruit = fruit;
	}

	public abstract void AfficherFruit();
}