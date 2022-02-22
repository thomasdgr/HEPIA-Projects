package dp;

public class Client {

	public Client() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		Fruit f1, f2, f3;
		Traitement dp;
		dp = new PauvreTraitement();
		f1 = new Banane(dp, "Banane", false);
		dp = new NormalTraitement();
		f2 = new Kiwi(dp, "Kiwi", false);
		dp = new EnrichiTraitement();
		f3 = new Mangue(dp, "Mangue", false);
		f1.AfficherCalories();
		f2.AfficherCalories();
		f3.AfficherCalories();
	}

}
