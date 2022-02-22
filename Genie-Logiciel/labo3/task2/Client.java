import factory.AbstractFactory;
import factory.SaladeFactory;
import factory.VapeurFactory;
import factory.CuissonFactory;
import factory.PotageFactory;

import herbes.Herbe;
import huiles.Huile;
import legumes.Legume;

public class Client {
	public static void main(String[] args) {
		System.out.println("Menu cuisson:");
        AbstractFactory f1 = new CuissonFactory();
		Legume l1 = f1.menuLegume();
		Herbe he1 = f1.menuHerbe();
		Huile hu1 = f1.menuHuile();
		l1.familleLegume();
		he1.familleHerbe();
		hu1.familleHuile();

		System.out.println("\nMenu potage:");
		AbstractFactory f2 = new PotageFactory();
		Legume l2 = f2.menuLegume();
		Herbe he2 = f2.menuHerbe();
		Huile hu2 = f2.menuHuile();
		l2.familleLegume();
		he2.familleHerbe();
		hu2.familleHuile();

		System.out.println("\nMenu salade:");
		AbstractFactory f3 = new SaladeFactory();
		Legume l3 = f3.menuLegume();
		Herbe he3 = f3.menuHerbe();
		Huile hu3 = f3.menuHuile();
		l3.familleLegume();
		he3.familleHerbe();
		hu3.familleHuile();

		System.out.println("\nMenu vapeur:");
		AbstractFactory f4 = new VapeurFactory();
		Legume l4 = f4.menuLegume();
		Herbe he4 = f4.menuHerbe();
		Huile hu4 = f4.menuHuile();
		l4.familleLegume();
		he4.familleHerbe();
		hu4.familleHuile();
	}
}