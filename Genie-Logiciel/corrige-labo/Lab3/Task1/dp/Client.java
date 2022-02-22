package dp;

import fabriques.Fabrique1;
import fabriques.FabriqueLegumeABS;
import fabriques.TypeLégume;
import legumes.Légume;

public class Client {

	public static void main(String[] args) {

		FabriqueLegumeABS f = new Fabrique1();
		Légume légume = f.creation(TypeLégume.CUISSON);
		légume.afficherLégume();
	}

}
