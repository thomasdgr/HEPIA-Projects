public class FruitPauvre extends Fruit{
    
    public FruitPauvre(Calories calories){
        super(calories);
    }

   @Override 
    public void AfficherCalories(){
        System.out.print("Le fruit pauvre \"" + getNom() + "\" possède ");
        System.out.println(this.calories.calculCalories(getNom()) +" calories pour 100 grammes");
    } 
}