public class Client{
    public static void main(String[] args){
        
        Fruit f1 = new FruitPauvre(new CaloriesPauvre());
        Fruit f2 = new FruitNormal(new CaloriesNormal());
        Fruit f3 = new FruitRiche(new CaloriesEnrichi());

        f1.setNom("Orange");
        f1.setPepin(true);

        f2.setNom("Banane");
        f2.setPepin(false);

        f3.setNom("Fraise");
        f3.setPepin(true);

        f1.AfficherCalories();
        f2.AfficherCalories();
        f3.AfficherCalories();

        f1.setNom("Ananas");
        f1.setPepin(false);
        f1.AfficherCalories();
    }
}