package factory;

import herbes.Herbe;
import herbes.Herbe4;
import huiles.Huile;
import huiles.Huile4;
import legumes.Legume;
import legumes.LegumeVapeur;

public class VapeurFactory extends AbstractFactory{
	public VapeurFactory(){}

	@Override
	public Legume menuLegume(){
		return new LegumeVapeur();
	}

	@Override
	public Huile menuHuile(){
		return new Huile4();
	}

	@Override
	public Herbe menuHerbe(){
		return new Herbe4();
	}
}