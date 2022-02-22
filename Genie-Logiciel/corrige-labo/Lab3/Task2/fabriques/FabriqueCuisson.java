package fabriques;

import herbes.Herbe;
import herbes.HerbesVerte;
import huiles.Huile;
import huiles.HuilesVierge;
import legumes.Légume;
import legumes.LégumesCuisson;

public class FabriqueCuisson extends FabriqueAbs {

	@Override
	public Légume creationLegume() {
		return new LégumesCuisson();
	}

	@Override
	public Huile creationHuile() {
		return new HuilesVierge();
	}

	@Override
	public Herbe creationHerbe() {
		return new HerbesVerte();
	}

}
