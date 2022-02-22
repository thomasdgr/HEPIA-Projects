package dp;

public class Client {

	public Client() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		Fruit f1, f2, f3, f4, f5, f6;
		Calories dp;

		dp = new PauvreTraitement();
		f1 = new Fruit(dp, "Banane", false);
		dp = new NormalTraitement();
		f2 = new Fruit(dp, "Kiwi", true);
		dp = new EnrichiTraitement();
		f3 = new Fruit(dp, "Mangue", false);
		dp = new EnrichiTraitement();
		f4 = new Fruit(dp, "Pastèque", true);
		dp = new EnrichiTraitement();
		f5 = new Fruit(dp, "Orange", false);
		dp = new EnrichiTraitement();
		f6 = new Fruit(dp, "Poire", true);

		Paniers_de_Fruits panier = new Paniers_de_Fruits(dp, null, null); //
		panier.add(f1);
		panier.add(f2);
		panier.add(f3);
		panier.add(f4);
		panier.add(f6);

		panier.afficherFruit();

		Paniers_de_Fruits panier2 = new Paniers_de_Fruits(dp, null, null); //
		panier2.add(f1);
		panier2.add(f3);
		panier2.remove(f5);

		panier2.afficherFruit();

	}

}
