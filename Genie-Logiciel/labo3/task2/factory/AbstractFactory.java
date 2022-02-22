package factory;

import herbes.Herbe;
import huiles.Huile;
import legumes.Legume;

public abstract class AbstractFactory {
	public abstract Legume menuLegume();

	public abstract Huile menuHuile();

	public abstract Herbe menuHerbe();
}
