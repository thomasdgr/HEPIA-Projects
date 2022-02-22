package fabriques;

import herbes.Herbe;
import huiles.Huile;
import legumes.Légume;

public abstract class FabriqueAbs {
	public abstract Légume creationLegume();

	public abstract Huile creationHuile();

	public abstract Herbe creationHerbe();
}
