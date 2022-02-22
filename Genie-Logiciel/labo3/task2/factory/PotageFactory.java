package factory;

import herbes.Herbe;
import herbes.Herbe2;
import huiles.Huile;
import huiles.Huile2;
import legumes.Legume;
import legumes.LegumePotage;

public class PotageFactory extends AbstractFactory{
	public PotageFactory(){}

	@Override
	public Legume menuLegume(){
		return new LegumePotage();
	}

	@Override
	public Huile menuHuile(){
		return new Huile2();
	}

	@Override
	public Herbe menuHerbe(){
		return new Herbe2();
	}
}