package dp;

public class Poire extends Fruit {
	private String _nom;
	private Boolean _pepin;

	public Poire(Traitement dp, String nom, Boolean pepin) {
		// TODO Auto-generated constructor stub
		super(dp);
		_nom = nom;
		_pepin = pepin;
	}

	public String AfficherCalories() {
		String calories = calculCalories(_nom);
		return calories;
	}

}