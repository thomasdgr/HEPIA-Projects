package fabriques;

import herbes.Herbe;
import herbes.HerbesParfumées;
import huiles.Huile;
import huiles.HuilesSpéciale;
import legumes.Légume;
import legumes.LégumesVapeur;

public class FabriqueVapeur extends FabriqueAbs {
	public Légume creationLegume() {
		return new LégumesVapeur();
	}

	@Override
	public Huile creationHuile() {
		return new HuilesSpéciale();
	}

	@Override
	public Herbe creationHerbe() {
		return new HerbesParfumées();
	}
}
