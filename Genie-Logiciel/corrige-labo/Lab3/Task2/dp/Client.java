package dp;

import fabriques.FabriqueAbs;
import fabriques.FabriqueSalades;
import herbes.Herbe;
import huiles.Huile;
import legumes.Légume;

public class Client {

	public static void main(String[] args) {
		FabriqueAbs f = new FabriqueSalades();
		Herbe herbe = f.creationHerbe();
		Huile huile = f.creationHuile();
		Légume legume = f.creationLegume();
		legume.afficherLégume();
		herbe.afficherHerbe();
		huile.afficherHuile();

	}

}
