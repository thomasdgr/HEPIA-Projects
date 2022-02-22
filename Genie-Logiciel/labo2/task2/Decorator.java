public abstract class Decorator extends Fruit {
    private Fruit fruit;

	public Decorator(Fruit fruit){
		super();
		this.fruit = fruit;
	}

	public abstract void AfficherFruit();
}