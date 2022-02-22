package dp;

public class Fruit {

	private String nom;
	private Boolean pepin;

	public Fruit() {
		// TODO Auto-generated constructor stub
	}

	public String getNom() {
		return nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public Boolean getPepin() {
		return pepin;
	}

	public void setPepin(Boolean pepin) {
		this.pepin = pepin;
	}

	public void AfficherFruit(String nom, Boolean pepin) {
		if (pepin) {
			System.out.println("Le fruit: " + nom + " a des pepins");
		} else {
			System.out.println("Le fruit: " + nom + " n'a pas de pepins");
		}
	}

}
