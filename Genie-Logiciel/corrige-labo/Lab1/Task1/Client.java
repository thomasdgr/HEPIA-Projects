package dp;

public class Client {

	public Client() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		Fruit f1 = new Fruit();
		Fruit f2 = new Fruit();
		Fruit f3 = new Fruit();

		f1.setNom("banane");
		f1.setPepin(false);
		f2.setNom("kiwi");
		f2.setPepin(true);
		f3.setNom("pomme");
		f3.setPepin(true);

		f1.AfficherFruit(f1.getNom(), f1.getPepin());
		f2.AfficherFruit(f2.getNom(), f2.getPepin());
		f3.AfficherFruit(f3.getNom(), f3.getPepin());
	}

}
