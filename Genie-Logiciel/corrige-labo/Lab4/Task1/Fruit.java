package dp;

public class Fruit {

	private String _nom;
	private Boolean _pepin;

	private Calories _dp;

	Fruit(Calories dp) {
		_dp = dp;
	}

	public Fruit(Calories dp, String nom, Boolean pepin) {
		// TODO Auto-generated constructor stub
		_dp = dp;
		_nom = nom;
		_pepin = pepin;
	}

	public String getNom() {
		return _nom;
	}

	public void setNom(String nom) {
		_nom = nom;
	}

	public Boolean getPepin() {
		return _pepin;
	}

	public void setPepin(Boolean pepin) {
		_pepin = pepin;
	}

	public int calculerCalories() {
		return _dp.traiterCalories(_nom);
	}

	public void afficherFruit() {
		if (_pepin == true) {
			System.out.println(
					"Le fruit: " + _nom + " a des pepins et possède: " + calculerCalories() + " calories/100g");
		} else {
			System.out.println(
					"Le fruit: " + _nom + " n'a pas de pepins et possède: " + calculerCalories() + " calories/100g");
		}
	}
}
