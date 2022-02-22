public class Client{
    public static void main(String[] args){        
        Fruit f1 = new Fruit();
        Fruit f2 = new Fruit();
        Fruit f3 = new Fruit();
        
        f1.setNom("Orange");
        f1.setPepin(true);
        
        f2.setNom("Banane");
        f2.setPepin(false);
        
        f3.setNom("Ananas");
        f3.setPepin(false);
                
        Panier p = new Panier();
        p.addFruit(f1);
        p.addFruit(f2);
        p.addFruit(f3);
        
        Decorator d1 = new DecoratorStar(p);
        Decorator d2 = new DecoratorEgal(f1);
        Decorator d3 = new DecoratorHashtag(p);

        d1.AfficherFruit();
        System.out.println();
        
        d2.AfficherFruit();
        System.out.println();
        
        d3.AfficherFruit();
        System.out.println();    
    }
}