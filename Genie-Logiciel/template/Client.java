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

        Fruit f4 = new FruitNormal(new CaloriesNormal());
        f4.setNom("Ananas");
        f4.setPepin(false);        

        Fruit[] fruits = {f1,f2,f3,f4};
        Commande c = Commande.getInstance();
        c.setContent(fruits);

        Panier p = new Panier();
        for(Fruit f: fruits){
            p.addFruit(f);
        }
        Decorator d1 = new DecoratorStar(p);
        d1.AfficherFruit();

        System.out.println("\nCommande:");
        c.AfficherCommande();

        System.out.println();

        c.TraiterCommande();
        c.TraiterCommande();
    }
}