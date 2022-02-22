package dp;

abstract class Fruit {
	abstract public void AfficherCalories(); // ATTENTION

	private String _nom;
	private Boolean _pepin;

	private Traitement _dp;

	Fruit(Traitement dp) {
		_dp = dp;
	}
	/*
	 * public Fruit(Affichage dp, String nom, Boolean pepin) { // TODO
	 * Auto-generated constructor stub _dp = dp; _nom = nom; // type _pepin =
	 * pepin; }
	 */

	public String getNom() {
		return _nom;
	}

	public void setNom(String nom) {
		this._nom = nom;
	}

	public Boolean getPepin() {
		return _pepin;
	}

	public void setPepin(Boolean pepin) {
		this._pepin = pepin;
	}

	public void calculCalories(String nom) {
		_dp.traiteCalories(nom);
	}

}
