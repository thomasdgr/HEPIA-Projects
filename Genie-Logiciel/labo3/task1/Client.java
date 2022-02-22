import factory.Factory;
import factory.FactoryLegume;
import legumes.Legume;

public class Client{
    public static void main(String[] args){
        Factory factoryLegume = new FactoryLegume();

        Legume l1 = factoryLegume.menu("Salade");
        l1.familleLegume();

        Legume l2 = factoryLegume.menu("Potage");
        l2.familleLegume();

        Legume l3 = factoryLegume.menu("Vapeur");
        l3.familleLegume();

        Legume l4 = factoryLegume.menu("Cuisson");
        l4.familleLegume();
    }
}
