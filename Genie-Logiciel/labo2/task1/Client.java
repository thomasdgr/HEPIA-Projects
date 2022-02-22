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
        p.AfficherFruit();

        System.out.println();
        p.removeFruit(f1);
        f1.setNom("Framboise");
        f1.setPepin(false);
        p.addFruit(f1);
        p.AfficherFruit();
    }
}