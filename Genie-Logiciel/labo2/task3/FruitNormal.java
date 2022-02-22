public class FruitNormal extends Fruit{
    
    public FruitNormal(Calories calories){
        super(calories);
    }

   @Override 
    public void AfficherCalories(){
        System.out.print("Le fruit normal \"" + getNom() + "\" possède ");
        System.out.println(this.calories.calculCalories(getNom()) +" calories pour 100 grammes");
    } 
}