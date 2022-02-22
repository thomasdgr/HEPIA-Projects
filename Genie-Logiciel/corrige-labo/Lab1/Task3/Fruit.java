package dp;

abstract class Fruit {
	abstract public String AfficherCalories(); // ATTENTION

	private String _nom;
	private Boolean _pepin;

	private String _calories_type; // solution provisoire

	private Traitement _dp;

	Fruit(Traitement dp) {
		_dp = dp;
	}

	public Fruit() {
	}

	public Fruit(Traitement dp, String nom, Boolean pepin) {
		_dp = dp;
		_nom = nom;
		_pepin = pepin;
	}

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

	public String get_calories_type() {
		return _calories_type;
	}

	public void set_calories_type(String _calories_type) {
		this._calories_type = _calories_type;
	}

	public String calculCalories(String nom) {
		String calories = _dp.traiteCalories(nom);
		return calories;
	}
}
