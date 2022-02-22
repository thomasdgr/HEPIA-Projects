9public class Client{
    public static void main(String[] args){
        Fruit f1 = new Fruit();
        Fruit f2 = new Fruit();

        f1.setNom("Orange");
        f1.setPepin(true);

        f2.setNom("Banane");
        f2.setPepin(false);

        f1.AfficherFruit();
        f2.AfficherFruit();

        System.out.println();

        f2.setNom("Ananas");
        f2.setPepin(false);

        f1.AfficherFruit();
        f2.AfficherFruit();
    }
}