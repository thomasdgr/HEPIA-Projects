package dp;

class Kiwi extends Fruit {
	private String _nom;
	private Boolean _pepin;

	public Kiwi(Traitement dp, String nom, Boolean pepin) {
		// TODO Auto-generated constructor stub
		super(dp);
		_nom = nom;
		_pepin = pepin;
	}

	public void AfficherCalories() {
		calculCalories(_nom);
	}

}