package dp;

public class Client {

	public Client() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		Fruit f1, f2, f3, f4, f5, f6;
		Traitement dp;
		Commande singleton;

		dp = new PauvreTraitement();
		f1 = new Banane(dp, "Banane", false);
		dp = new NormalTraitement();
		f2 = new Kiwi(dp, "Kiwi", false);
		dp = new EnrichiTraitement();
		f3 = new Mangue(dp, "Mangue", false);
		dp = new EnrichiTraitement();
		f4 = new Mangue(dp, "Pastèque", true);
		dp = new EnrichiTraitement();
		f5 = new Mangue(dp, "Orange", false);
		dp = new EnrichiTraitement();
		f6 = new Mangue(dp, "Poire", true);
		/*
		 * Lab1 - Tâche 2 f1.AfficherCalories(); f2.AfficherCalories();
		 * f3.AfficherCalories(); f4.AfficherCalories(); f5.AfficherCalories();
		 * f6.AfficherCalories();
		 */
		f1.setNom("Banane");
		f1.setPepin(false);
		f1.set_calories_type("Pauvre"); // Provisoire
		f2.setNom("kiwi");
		f2.setPepin(true);
		f2.set_calories_type("Normal"); // Provisoire
		f3.setNom("Mangue");
		f3.setPepin(true);
		f3.set_calories_type("Enrichi"); // Provisoire
		f4.setNom("Pastèque");
		f4.setPepin(true);
		f4.set_calories_type("Enrichi"); // Provisoire
		f5.setNom("Orange");
		f5.setPepin(false);
		f5.set_calories_type("Enrichi"); // Provisoire
		f6.setNom("Poire");
		f6.setPepin(true);
		f6.set_calories_type("Enrichi"); // Provisoire

		singleton = Commande.getInstance();
		singleton.ajouter(f1);
		singleton = Commande.getInstance();
		singleton.ajouter(f2);
		singleton = Commande.getInstance();
		singleton.ajouter(f3);
		singleton = Commande.getInstance();
		singleton.ajouter(f4);
		singleton = Commande.getInstance();
		singleton.ajouter(f5);
		singleton = Commande.getInstance();
		singleton.ajouter(f6);

		;

	}

}
