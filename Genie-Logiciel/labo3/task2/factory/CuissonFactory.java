package factory;

import herbes.Herbe;
import herbes.Herbe1;
import huiles.Huile;
import huiles.Huile1;
import legumes.Legume;
import legumes.LegumeCuisson;

public class CuissonFactory extends AbstractFactory{
	public CuissonFactory(){}

	@Override
	public Legume menuLegume(){
		return new LegumeCuisson();
	}

	@Override
	public Huile menuHuile(){
		return new Huile1();
	}

	@Override
	public Herbe menuHerbe(){
		return new Herbe1();
	}
}