public class FruitRiche extends Fruit{
    
    public FruitRiche(Calories calories){
        super(calories);
    }

   @Override 
    public void AfficherCalories(){
        System.out.print("Le fruit riche \"" + getNom() + "\" possède ");
        System.out.println(this.calories.calculCalories(getNom()) +" calories pour 100 grammes");
    } 
}