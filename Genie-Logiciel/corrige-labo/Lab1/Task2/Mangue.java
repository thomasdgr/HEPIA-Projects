package dp;

class Mangue extends Fruit {
	private String _nom;
	private Boolean _pepin;

	public Mangue(Traitement dp, String nom, Boolean pepin) {
		// TODO Auto-generated constructor stub
		super(dp);
		_nom = nom;
		_pepin = pepin;
	}

	public void AfficherCalories() {
		calculCalories(_nom);
	}

}
