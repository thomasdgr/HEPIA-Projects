package factory;

import herbes.Herbe;
import herbes.Herbe3;
import huiles.Huile;
import huiles.Huile3;
import legumes.Legume;
import legumes.LegumeSalade;

public class SaladeFactory extends AbstractFactory{
	public SaladeFactory(){}

	@Override
	public Legume menuLegume(){
		return new LegumeSalade();
	}

	@Override
	public Huile menuHuile(){
		return new Huile3();
	}

	@Override
	public Herbe menuHerbe(){
		return new Herbe3();
	}
}