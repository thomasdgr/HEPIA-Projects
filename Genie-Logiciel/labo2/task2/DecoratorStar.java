public class DecoratorStar extends Decorator {
    protected Fruit fruit;

    public DecoratorStar(Fruit f){
        super(f);
        this.fruit = f;
    }

    @Override 
    public void AfficherFruit(){
        for(int i = 0; i < 20; i++){
            System.out.print("*");
        }
        System.out.print("\n\n");
        fruit.AfficherFruit();
        System.out.print("\n");
        
        for(int i = 0; i < 20; i++){
            System.out.print("*");
        }
        System.out.print("\n");
    }
} 