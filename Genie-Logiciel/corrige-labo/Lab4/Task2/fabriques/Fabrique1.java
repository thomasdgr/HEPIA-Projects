package fabriques;

import legumes.Légume;
import legumes.LégumesCuisson;
import legumes.LégumesFour;
import legumes.LégumesPotages;
import legumes.LégumesSalades;
import legumes.LégumesVapeur;

public class Fabrique1 extends FabriqueLegumeABS {

	public Légume creation(TypeLégume type) {
		switch (type) {
		case CUISSON:
			return new LégumesCuisson();

		case POTAGES:
			return new LégumesPotages();

		case SALADES:

			return new LégumesSalades();

		case VAPEUR:

			return new LégumesVapeur();
		case FOUR:

			return new LégumesFour();
		default:
			break;
		}
		return null;
	}

}
