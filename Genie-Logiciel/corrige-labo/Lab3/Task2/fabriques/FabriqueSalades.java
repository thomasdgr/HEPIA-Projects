package fabriques;

import herbes.Herbe;
import herbes.HerbesFraiches;
import huiles.Huile;
import huiles.HuilesLégère;
import legumes.Légume;
import legumes.LégumesSalades;

public class FabriqueSalades extends FabriqueAbs {

	@Override
	public Légume creationLegume() {
		return new LégumesSalades();
	}

	@Override
	public Huile creationHuile() {
		return new HuilesLégère();
	}

	@Override
	public Herbe creationHerbe() {
		return new HerbesFraiches();
	}
}
