package fabriques;

import herbes.Herbe;
import herbes.HerbesFortes;
import huiles.Huile;
import huiles.HuilesForte;
import legumes.Légume;
import legumes.LégumesPotages;

public class FabriquePotages extends FabriqueAbs {

	@Override
	public Légume creationLegume() {
		return new LégumesPotages();
	}

	@Override
	public Huile creationHuile() {
		return new HuilesForte();
	}

	@Override
	public Herbe creationHerbe() {
		return new HerbesFortes();
	}

}
